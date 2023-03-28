//
// Created by dave on 27.03.23.
//

#include <engine/particle.h>
#include <iostream>
using namespace engine;

void Particle::clearForceStorage() {
    storedForce.x = 0.0;
    storedForce.y = 0.0;
}

void Particle::integrate(real duration) {
    // Ensure we don't perform integration on objects with infinite mass
    if (invertedMass <= 0.0f) return;

    // Update position
    position.addScaledVector(velocity, duration);
    std::cout << "Position: " << position.x << " " << position.y << std::endl;

    // Calculate acceleration from the force
    Vector acc = acceleration;
    std::cout << "Acc: " << acc.x << " " << acc.y << std::endl;

    // Update velocity with the acceleration
    velocity.addScaledVector(acc, duration);
    std::cout << "Velocity: " << " " << velocity.x << velocity.y << std::endl;

    // Reduce the velocity with each frame
    velocity *= real_pow(damping, duration);
    std::cout << "Velocity after damping: " << " " << velocity.x << velocity.y << std::endl;

    // Clear the forces after calculations
    clearForceStorage();
}

void Particle::setMass(real mass) {
    // Ensure mass not equal to 0
    if(mass <= 0) { return; }

    // invertedMass used for acceleration calculation
    Particle::invertedMass = 1/mass;
}


Vector Particle::getPosition() const {
    return position;
}

void Particle::getPosition(Vector *pos) const {
    *pos = Particle::position;
}

void Particle::setVelocity(const Vector &velocity) {
    Particle::velocity = velocity;
}

void Particle::setDamping(real damping) {
    Particle::damping = damping;
}

void Particle::setAcceleration(const Vector &acc) {
    Particle::acceleration = acc;
}

void Particle::setPosition(engine::real x, engine::real y, engine::real z) {
    Particle::position = Vector(x, y, z);
}



