//
// Created by dave on 27.03.23.
//

#include <engine/particle.h>
#include <cassert>

using namespace engine;

void Particle::setMass(real mass) {
    // Ensure mass not equal to 0
    if(mass <= 0.0f) { return; }

    // invertedMass used for acceleration calculation
    Particle::invertedMass = real(1.0f)/mass;
}

void Particle::setVelocity(const Vector &vel) {
    Particle::velocity = vel;
}

void Particle::setVelocity(real x, real y) {
    Particle::velocity.x = x;
    Particle::velocity.y = y;
}

void Particle::setAcceleration(const Vector &acc) {
    Particle::acceleration = acc;
}

void Particle::setAcceleration(real x, real y) {
    Particle::acceleration.x = x;
    Particle::acceleration.y = y;
}

void Particle::setPosition(engine::real x, engine::real y) {
    Particle::position = Vector(x, y);
}

void Particle::setPosition(const Vector &pos) {
    Particle::position = pos;
}

void Particle::setDamping(real value) {
    Particle::damping = value;
}

Vector Particle::getAcceleration() const {
    return acceleration;
}

Vector Particle::getVelocity() const {
    return velocity;
}

Vector Particle::getPosition() const {
    return position;
}

real Particle::getMass() const {
    return invertedMass;
}

void Particle::clearForceStorage() {
    Particle::forceStorage = Vector(0.0f, 0.0f);
}

void Particle::addForce(Vector force) {
    Particle::forceStorage += force;
}

void Particle::integrate(real delta) {
    /**
     * Code adapted from Millington, 2010
     */
    // Ensure we don't perform integration on objects with infinite mass
    if (invertedMass <= 0.0f) return;
    assert(delta > 0.0f);

    // Update position
    position.addScaledVector(velocity, delta);

    // Calculate acceleration from the force
    Vector acc = acceleration;

    // Add stored forces from previous frame
    acc.addScaledVector(forceStorage, invertedMass);

    // Update velocity with the acceleration
    velocity.addScaledVector(acc, delta);

    // Reduce the velocity with each frame
    velocity *= real_pow(damping, delta);

    // Clear the forces after calculations
    clearForceStorage();
    /**
     * End of adapted code
     */

    setAcceleration(Vector(0.0f, 0.0f));
}
