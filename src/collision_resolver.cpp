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

    for (auto& collision : collisions) {
        // Resolve collision between static objects
        if (collision.object1->objectType == WALL) {
            resolveWallCollision(collision.object2);
            continue;
        }

        if (collision.object2->objectType == WALL) {
            resolveWallCollision(collision.object1);
            continue;
        }

        if(collision.object1->objectType == FLOOR) {
            resolveFloorCollision(collision.object2);
            continue;
        }

        if(collision.object2->objectType == FLOOR) {
            resolveFloorCollision(collision.object1);
            continue;
        }

        // Resolve collision between dynamic objects
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

    // Calculate the separating velocity
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

    // Resolve intersection
//    resolveIntersection(gameObject1, gameObject2);
}


void CollisionResolver::resolveWallCollision(GameObject *collider) const {
    Particle* wallCollider = collider->getParticle();
    Vector contactNormal;

    // Check if it is a left or right wall
    if (wallCollider->getPosition().x < 100.0f) {
        contactNormal = Vector(wallCollider->getPosition().x * -0.9f, wallCollider->getPosition().y) - wallCollider->getPosition();
    } else {
        contactNormal = Vector(wallCollider->getPosition().x * 1.1f, wallCollider->getPosition().y) - wallCollider->getPosition();
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

void CollisionResolver::resolveFloorCollision(GameObject *collider) const {
    Particle* floorCollider = collider->getParticle();

    // Calculate Fn - Normal force
    Vector gravity = {0.0f, -25.0f};
    real inverseMass = floorCollider->getInvertedMass();
    Vector normalForce = gravity * inverseMass * -1.0f;

    Vector colliderVelocity = floorCollider->getVelocity();

    if(colliderVelocity.y >= 0.0f) { return; }

    // Apply the normal force to the collider object
    floorCollider->addForce(normalForce);

    // Update the velocity of the collider object
    Vector newVelocity = colliderVelocity + colliderVelocity * -contactCoefficient * 2.0f;
    floorCollider->setVelocity(-newVelocity.x, newVelocity.y);
}