//
// Created by dave on 27.03.23.
//

#include <engine/particle.h>

using namespace engine;

void Particle::clearForces() {
    // reset the acceleration
    acceleration = {0.0, 0.0, 0.0};
}

void Particle::integrate(real duration) {
    // Ensure we don't perform integration on objects with infinite mass
    if (invertedMass <= 0.0f) return;

    // Update position
    position.addScaledVector(velocity, duration);

    // Calculate acceleration from the force
    Vector acc = acceleration;

    // Update velocity with the acceleration
    position.addScaledVector(acc, duration);

    // Reduce the velocity with each frame
    velocity *= real_pow(damping, duration);

    // Clear the forces after calculations
    clearForces();
}

