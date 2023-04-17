//
// Created by dave on 28.03.23.
//

#include "ball.h"

Ball::Ball(real rad) {
    /** Initialise variables */
    radius = rad;

    /** Set the Ball "randomly" in the scene */
    srand(static_cast <unsigned> (time(0)));
    auto x = static_cast <float> (rand() % 700);
    x += real(1.555) * radius;
    real y = 150.0f;
    circleShape.setRadius(radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});
    circleShape.setPosition(x, y);

    /** Initialise Particle variables */
    ballParticle.setMass(real(0.2) * rad);
    ballParticle.setDamping(0.95f);
    ballParticle.setVelocity(0.0f, radius * 1.5f, 0.0f);
    ballParticle.setAcceleration(0.0f, -5.0f, 0.0f);
    ballParticle.setPosition(x, y, 0.0f);
}

Ball::~Ball() = default;

void Ball::update(real delta, sf::Window &window) {
    // Apply forces to the Ball
    calculateForces();

    if (ballParticle.getPosition().y < 85.0f + radius) {
        ballParticle.setAcceleration(0.0f, 150.0f, 0.0f);
    }

    // Perform integration
    ballParticle.integrate(delta);
    Vector newPosition = ballParticle.getPosition();

    // fix conventional coordinates system into screen coordinates system
    circleShape.setPosition(newPosition.x, real(window.getPosition().y) - newPosition.y);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}

void Ball::move(Vector acc) {
    ballParticle.setAcceleration(acc);
}

void Ball::jump() {
    Vector jumpAcc = {0.0f, 100.0f, 0.0f};
    ballParticle.setAcceleration(jumpAcc);
}
Vector Ball::getCurrentAcceleration() {
    return ballParticle.getAcceleration();
}

Vector Ball::getCurrentVelocity() {
    return ballParticle.getVelocity();
}

Vector Ball::getCurrentPosition() {
    return ballParticle.getPosition();
}

void Ball::calculateForces() {
    gravityForce.updateForce(&ballParticle);
    dragForce.updateForce(&ballParticle);
}

