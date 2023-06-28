//
// Created by dave on 17.04.23.
//
#include "engine/collision_resolver.h"
#include <iostream>
using namespace engine;

void CollisionResolver::addCollision(GameObject* object1, GameObject* object2) {
    Collision newCollision = {object1, object2};
    collisions.push_back(newCollision);
}

void CollisionResolver::resolve() {

    if (collisions.size() < 2) return;

    for (auto & collision : collisions) {
        if (collision.object1->objectType == WALL) {
            resolveWallCollision(collision.object2, collision.object1);
            continue;
        }

        if (collision.object2->objectType == WALL) {
            resolveWallCollision(collision.object1, collision.object2);
            continue;
        }

        if(collision.object1->objectType == FLOOR) {
            resolveFloorCollision(collision.object2, collision.object1);
            continue;
        }

        if(collision.object2->objectType == FLOOR) {
            resolveFloorCollision(collision.object1, collision.object2);
            continue;
        }
        // If not wall or floor collision, resolve normal collision
        resolveCollision(collision.object1, collision.object2);
    }

    removeResolvedCollisions();
}

void CollisionResolver::removeResolvedCollisions() {
    std::cout << "Removing resolved collisions - " << collisions.size() << std::endl;
    collisions.clear();
}

void CollisionResolver::resolveCollision(GameObject* gameObject1, GameObject* gameObject2) {
    // Get particles
    Particle* collider = gameObject1->getParticle();
    Particle* otherCollider = gameObject2->getParticle();

    // Calculate the contact direction
    contactDirection = otherCollider->getPosition() - collider->getPosition();
    contactDirection.normalize();
    contactDirection.invert();

    Vector velocityDifference = collider->getVelocity() - otherCollider->getVelocity();
    real separatingVelocity = velocityDifference.getScalarProduct(contactDirection);

    // Check if it needs to be resolved, return if not
    if (separatingVelocity > 0.0f) { return; }

    real separatingVelocityWithCoefficient = real(-1.f) * separatingVelocity * contactCoefficient;
    real differenceInVel = separatingVelocityWithCoefficient - separatingVelocity;

    // Ensure we are not resolving collision for objects with infinite mass
    real sumOfInvertedMasses = collider->getInvertedMass() + otherCollider->getInvertedMass();
    if (sumOfInvertedMasses <= 0.0f) { return; }

    Vector resultingImpulse = contactDirection * (differenceInVel / sumOfInvertedMasses);

    // Apply impulse directly to the velocity for ParticleOne
    Vector object1Impulse = collider->getVelocity() + resultingImpulse * collider->getInvertedMass();
    collider->setVelocity(object1Impulse);

    // Apply impulse directly to the velocity for ParticleTwo
    Vector object2Impulse = otherCollider->getVelocity() + resultingImpulse * otherCollider->getInvertedMass() * real(-1);
    otherCollider->setVelocity(object2Impulse);
}


void CollisionResolver::resolveWallCollision(GameObject *collider, GameObject* wall) const {
    Particle* wallCollider = collider->getParticle();
    Vector contactNormal;

    if (wallCollider->getPosition().x < 100.0f) {
        contactNormal = Vector(wallCollider->getPosition().x * -0.9f, wallCollider->getPosition().y) - wallCollider->getPosition();
    } else {
        contactNormal = Vector(wallCollider->getPosition().x * 1.2f, wallCollider->getPosition().y) - wallCollider->getPosition();
    }

    contactNormal.normalize();
    contactNormal.invert();

    Vector colliderVel = wallCollider->getVelocity() - Vector(wallCollider->getVelocity().x * -1.2f, 0.0f);
    real separatingVelocity = colliderVel.getScalarProduct(contactNormal);

    // Check if it needs to be resolved, return if not
    if (separatingVelocity > 0.0f) { return; }

    real separatingVelocityWithCoefficient = real(-1.0f) * separatingVelocity * contactCoefficient;
    real differenceInVel = separatingVelocityWithCoefficient - separatingVelocity;

    real invertedMasses = wallCollider->getInvertedMass() + wallCollider->getInvertedMass();
    Vector resultingImpulse = contactNormal * (differenceInVel / invertedMasses);

    // Apply impulse directly to the velocity for wallCollider
    Vector wallColliderImpulse = wallCollider->getVelocity() + resultingImpulse * wallCollider->getInvertedMass();
    wallCollider->setVelocity(wallColliderImpulse);
}

void CollisionResolver::resolveFloorCollision(GameObject *collider, GameObject* floor) const {
    Particle* floorCollider = collider->getParticle();

    // Calculate Fn - Normal force
    Vector gravity = {0.0f, -25.0f};
    real inverseMass = floorCollider->getInvertedMass();
    Vector normalForce = gravity * inverseMass * -0.5f;

    // Calculate the velocity after collision (bounce or restitution)
    Vector colliderVelocity = floorCollider->getVelocity();

    if(colliderVelocity.y >= 0.0f) { return; }
    // Apply the normal force to the collider object
    floorCollider->setAcceleration(normalForce);

    // Update the velocity of the collider object
    Vector newVelocity = colliderVelocity + colliderVelocity * -contactCoefficient + normalForce;
    floorCollider->setVelocity(newVelocity.x, newVelocity.y);
}

void CollisionResolver::resolveIntersection(GameObject *gameObject1, GameObject *gameObject2) const {
//
    // Calculate intersection depth based on the bounding boxes
    real intersectionDepthX = fmin(gameObject1->getBoundingBox().xMax, gameObject2->getBoundingBox().xMax) - fmax(gameObject1->getBoundingBox().xMin, gameObject2->getBoundingBox().xMin);
    real intersectionDepthY = fmin(gameObject1->getBoundingBox().yMax, gameObject2->getBoundingBox().yMax) - fmax(gameObject1->getBoundingBox().yMin, gameObject2->getBoundingBox().yMin);

    // Calculate the total intersection depth
    real totalIntersectionDepth = (intersectionDepthX + intersectionDepthY) / 2;

    // If the objects are not intersecting, the intersection depths will be negative or zero
    if (totalIntersectionDepth > 0.0f) {

        std::cout << "intersection depth: " << totalIntersectionDepth << std::endl;

        // Use the totalIntersectionDepth to resolve the collision between the objects
        Particle* object1 = gameObject1->getParticle();
        Particle* object2 = gameObject2->getParticle();

        real totalInvertedMass = object1->getInvertedMass() + object2->getInvertedMass();

        if (totalInvertedMass <= 0.0f) return;

        Vector distance = object1->getPosition() - object2->getPosition();
        distance.normalize();

        Vector displacement = distance * (totalIntersectionDepth / totalInvertedMass);

        object1->setPosition(object1->getPosition() + (displacement * 0.2f * object1->getInvertedMass()));
        object2->setPosition(object2->getPosition() - (displacement * 0.2f * object2->getInvertedMass()));
    }

}

