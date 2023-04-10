//
// Created by dave on 27.03.23.
//

#include <engine/particle.h>

using namespace engine;
/**
 * Code adapted from Millington, 2010
 */
void Particle::integrate(real duration) {
    // Ensure we don't perform integration on objects with infinite mass
    if (invertedMass <= 0.0f || duration <= 0.0) return;

    // Update position
    position.addScaledVector(velocity, duration);

    // Calculate acceleration from the force
    Vector acc = acceleration;

    // Add stored forces from previous frame
    // acc.addScaledVector(storedForce, invertedMass);

    // Update velocity with the acceleration
    velocity.addScaledVector(acc, duration);

    // Reduce the velocity with each frame
    velocity *= real_pow(damping, duration);

    // Clear the forces after calculations
    clearForceStorage();
}
/**
 * Code adapted from Millington, 2010
 */

Vector Particle::getPosition() const {
    return position;
}

void Particle::getPosition(Vector *pos) const {
    *pos = Particle::position;
}

void Particle::setMass(real mass) {
    // Ensure mass not equal to 0
    if(mass <= 0) { return; }

    // invertedMass used for acceleration calculation
    Particle::invertedMass = real(1)/mass;
}

void Particle::setVelocity(const Vector &velocity) {
    Particle::velocity = velocity;
}

void Particle::setVelocity(real x, real y, real z) {
    Particle::velocity.x = x;
    Particle::velocity.y = y;
    Particle::velocity.z = z;
}

void Particle::setDamping(real damping) {
    Particle::damping = damping;
}

void Particle::setAcceleration(const Vector &acc) {
    // Particle::acceleration = acc;
    Particle::acceleration += acc;
}

void Particle::setAcceleration(real x, real y, real z) {
    Particle::acceleration.x = x;
    Particle::acceleration.y = y;
    Particle::acceleration.z = z;
}

void Particle::setPosition(engine::real x, engine::real y, engine::real z) {
    Particle::position = Vector(x, y, z);
}

void Particle::clearForceStorage() {
    storedForce.x = 0.0;
    storedForce.y = 0.0;
}

void Particle::setStoredForce(const engine::Vector &force) {
    storedForce += force;
}
