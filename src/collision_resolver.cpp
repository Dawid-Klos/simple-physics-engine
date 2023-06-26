//
// Created by dave on 17.04.23.
//
#include "engine/collision_resolver.h"
#include <iostream>
using namespace engine;

void CollisionResolver::addCollision(GameObject* object1, GameObject* object2) {
    Collision new_collision = {object1, object2};
    collisions.push_back(new_collision);
}

void CollisionResolver::resolve() {

    if (collisions.size() < 2) return;

    for (auto & collision : collisions) {
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
    Particle* target = gameObject2->getParticle();

    // Calculate the contact direction
    contactDirection = target->getPosition() - collider->getPosition();
    contactDirection.normalize();
    contactDirection.invert();

    Vector velocityDifference = collider->getVelocity() - target->getVelocity();
    real separatingVelocity = velocityDifference.getScalarProduct(contactDirection);


    // Check if it needs to be resolved, return if not
    if (separatingVelocity > 0.0f) {

        // Check if one of the objects is a wall and resolve collision
        if(gameObject1->objectType == WALL) {
            // print collision info
//            std::cout << "WALL xMin: " << gameObject1->getBoundingBox().xMin << " xMax: " << gameObject1->getBoundingBox().xMax << " yMin: " << gameObject1->getBoundingBox().yMin << " yMax: " << gameObject1->getBoundingBox().yMax << std::endl;
//            std::cout << "BALL xMin: " << gameObject2->getBoundingBox().xMin << " xMax: " << gameObject2->getBoundingBox().xMax << " yMin: " << gameObject2->getBoundingBox().yMin << " yMax: " << gameObject2->getBoundingBox().yMax << std::endl;
//
            if (target->getPosition().y < 1.0f) {
                return;
            }
            Vector targetVel = target->getVelocity() * 0.6f;  // Adjust the velocity as desired
            targetVel.invert();
            target->setVelocity(targetVel);
        }

        // Check if one of the objects is a wall and resolve collision
        if(gameObject2->objectType == WALL) {
            if (collider->getPosition().y < 1.0f) {
                return;
            }
            Vector colliderVel = collider->getVelocity() * 0.6f;  // Adjust the velocity as desired
            colliderVel.invert();
            collider->setVelocity(colliderVel);
        }
        return;
    }

    real separatingVelocityWithCoefficient = real(-1.f) * separatingVelocity * contactCoefficient;
    real differenceInVel = separatingVelocityWithCoefficient - separatingVelocity;

    // Ensure we are not resolving collision for objects with infinite mass
    real sumOfInvertedMasses = collider->getInvertedMass() + target->getInvertedMass();
    if (sumOfInvertedMasses <= 0.0f) { return; }

    Vector resultingImpulse = contactDirection * (differenceInVel / sumOfInvertedMasses);

    // Apply impulse directly to the velocity for ParticleOne
    Vector object1Impulse = collider->getVelocity() + resultingImpulse * collider->getInvertedMass();
    collider->setVelocity(object1Impulse);

    // Apply impulse directly to the velocity for ParticleTwo
    Vector object2Impulse = target->getVelocity() + resultingImpulse * target->getInvertedMass() * real(-1);
    target->setVelocity(object2Impulse);
}


void CollisionResolver::resolveIntersection(GameObject* gameObject1, GameObject*  gameObject2) {
//    // Get particles
//    Particle& object1 = gameObject1->getParticle();
//    Particle& object2 = gameObject2->getParticle();
//
//    // Calculate the penetration depth
//    Vector distance = object2.getPosition() - object1.getPosition();
//    real distanceMagnitude = distance.getMagnitude();
//    // TODO: Implement intersection between different objects
//    real radiusSum = 30.0f;
////    real radiusSum = ball1.getRadius() + ball2.getRadius();
//
//
//    if (distanceMagnitude > radiusSum) {
//        // Calculate the displacement vector
//        distance.normalize();
//        Vector displacement = distance * (radiusSum - distanceMagnitude);
//
//        // Move the circle by the displacement
//        object1.setPosition(object1.getPosition() + (displacement * object1.getInvertedMass()));
//        object2.setPosition(object2.getPosition() - (displacement * object2.getInvertedMass()));
//    }
}


