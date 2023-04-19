//
// Created by dave on 17.04.23.
//
#include "engine/collision_resolver.h"
#include <iostream>
using namespace engine;

void CollisionResolver::addCollision(Particle *object1, Particle *object2) {
    collidingParticles.push_back(object1);
    collidingParticles.push_back(object2);
}

void CollisionResolver::resolve(real delta) {

    if (collidingParticles.size() < 2) return;
    Particle* object1 = collidingParticles[0];
    Particle* object2 = collidingParticles[1];

    // Calculate the contact direction
    contactDirection = object2->getPosition() - object1->getPosition();
    contactDirection.normalize();
    contactDirection.invert();

    Vector velocityDifference = object1->getVelocity() - object2->getVelocity();
    real separatingVelocity = velocityDifference.getScalarProduct(contactDirection);

    // Check if needs to be resolve, return if not
    if (separatingVelocity > 0.0f) { return; }

    real separatingVelocityWithCoefficient = real(-1) * separatingVelocity * contactCoefficient;
    real differenceInVel = separatingVelocityWithCoefficient - separatingVelocity;

    real sumOfInvertedMasses = object1->getMass() + object2->getMass();

    // Ensure we are not resolving collision for objects with infinite mass
    if (sumOfInvertedMasses < 0.0f) { return; }

    Vector resultingImpulse = contactDirection * (differenceInVel / sumOfInvertedMasses);

    // Apply impulse directly to the velocity for ParticleOne
    Vector particleOneImpulse = object1->getVelocity() + resultingImpulse * object1->getMass();
    object1->setVelocity(particleOneImpulse);

    // Apply impulse directly to the velocity for ParticleTwo
    Vector object2Impulse = object2->getVelocity() + resultingImpulse * object2->getMass() * real(-1);
    object2->setVelocity(object2Impulse);
}

void CollisionResolver::removeResolvedCollisions() {
    for (auto it = collidingParticles.begin(); it != collidingParticles.end();) {
        it = collidingParticles.erase(it);
    }
}

