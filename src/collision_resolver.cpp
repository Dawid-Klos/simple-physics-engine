//
// Created by dave on 17.04.23.
//
#include "engine/collision_resolver.h"
#include <iostream>
using namespace engine;

void CollisionResolver::addCollision(Particle *object1, Particle *object2) {
    Collision new_collision = {object1, object2};
    collisions.push_back(new_collision);
}

void CollisionResolver::resolve(real delta) {

    if (collisions.size() < 2) return;

    for (auto & collision : collisions) {
        resolveCollision(collision.particle1, collision.particle2);
    }

    removeResolvedCollisions();
}

void CollisionResolver::removeResolvedCollisions() {
    std::cout << "Removing resolved collisions - " << collisions.size() << std::endl;
    collisions.clear();
}

void CollisionResolver::resolveCollision(Particle* object1, Particle* object2) {

    // Calculate the contact direction
    contactDirection = object2->getPosition() - object1->getPosition();
    contactDirection.normalize();
    contactDirection.invert();

    Vector velocityDifference = object1->getVelocity() - object2->getVelocity();
    real separatingVelocity = velocityDifference.getScalarProduct(contactDirection);

    // Check if it needs to be resolved, return if not
    if (separatingVelocity > 0.0f) { return; }

    real separatingVelocityWithCoefficient = real(-1.f) * separatingVelocity * contactCoefficient;
    real differenceInVel = separatingVelocityWithCoefficient - separatingVelocity;

    // Ensure we are not resolving collision for objects with infinite mass
    real sumOfInvertedMasses = object1->getMass() + object2->getMass();
    if (sumOfInvertedMasses <= 0.0f) { return; }

    Vector resultingImpulse = contactDirection * (differenceInVel / sumOfInvertedMasses);

    // Apply impulse directly to the velocity for ParticleOne
    Vector object1Impulse = object1->getVelocity() + resultingImpulse * object1->getMass();
    object1->setVelocity(object1Impulse);

    // Apply impulse directly to the velocity for ParticleTwo
    Vector object2Impulse = object2->getVelocity() + resultingImpulse * object2->getMass() * real(-1);
    object2->setVelocity(object2Impulse);
}
