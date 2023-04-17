//
// Created by dave on 28.03.23.
//

#include "ball.h"

Ball::Ball(engine::real rad) {
    /** Initialise variables */
    radius = rad;

    /** Set the Ball "randomly" in the scene */
    srand(static_cast <unsigned> (time(0)));
    auto x = static_cast <float> (rand() % 700);
    x += engine::real(1.555) * radius;
    engine::real y = 150.0f;
    circleShape.setRadius(radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});
    circleShape.setPosition(x, y);

    /** Initialise Particle variables */
    ballParticle.setMass(engine::real(0.2) * rad);
    ballParticle.setDamping(0.95f);
    ballParticle.setVelocity(0.0f, radius * 1.5f, 0.0f);
    ballParticle.setAcceleration(0.0f, -5.0f, 0.0f);
    ballParticle.setPosition(x, y, 0.0f);
}

Ball::~Ball() = default;

void Ball::update(engine::real delta, sf::Window &window) {
    // Apply forces to the Ball
    calculateForces();

    if (ballParticle.getPosition().y < 80.0f) {
        ballParticle.setAcceleration(0.0f, radius * 2.0f, 0.0f);
    }

    // Perform integration
    ballParticle.integrate(delta);
    engine::Vector newPosition = ballParticle.getPosition();

//    if (newPosition.x < 0.0f) {
//        newPosition.x = 0.0f;
//    }
//    if (newPosition.x > 800.0f - circleShape.getRadius()) {
//        newPosition.x = 800.0f - circleShape.getRadius();
//    }
//    if (newPosition.y < 50.0f + circleShape.getRadius()) {
//        newPosition.y = 50.0f + circleShape.getRadius();
//    }
//    if (newPosition.y > 600.0f - circleShape.getRadius()) {
//        newPosition.y = 600.0f - circleShape.getRadius();
//    }

    // fix conventional coordinates system into screen coordinates system
    circleShape.setPosition(newPosition.x, engine::real(window.getPosition().y) - newPosition.y);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}

void Ball::move(engine::Vector acc) {
    ballParticle.setAcceleration(acc);
}

void Ball::jump() {
    engine::Vector jumpAcc = {0.0f, 100.0f, 0.0f};
    ballParticle.setAcceleration(jumpAcc);
}
engine::Vector Ball::getCurrentAcceleration() {
    return ballParticle.getAcceleration();
}

engine::Vector Ball::getCurrentVelocity() {
    return ballParticle.getVelocity();
}

engine::Vector Ball::getCurrentPosition() {
    return ballParticle.getPosition();
}

void Ball::calculateForces() {
    gravityForce.updateForce(&ballParticle);
    dragForce.updateForce(&ballParticle);
}

