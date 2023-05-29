//
// Created by dave on 28.03.23.
//

#include "ball.h"

Ball::Ball(real rad, real posX, real posY) {
    /** Initialise variables */
    radius = rad;

    /** Set the Ball shape object properties and position in the scene */
    circleShape.setRadius(radius);
    circleShape.setOrigin(radius, radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});
    circleShape.setPosition(posX, posY);

    /** Set the Particle object properties for physics calculations */
    ballParticle.setMass(real(0.1) * rad);
    ballParticle.setDamping(0.98f);
    ballParticle.setVelocity(145.0f, 245.0f, 0.0f);
    ballParticle.setAcceleration(-10.0f, 0.0f, 0.0f);
    ballParticle.setPosition(posX, posY, 0.0f);
}

Ball::~Ball() = default;

void Ball::update(real delta, sf::Window &window) {
    // Apply forces to the Ball
    calculateForces();

    // Perform integration
    ballParticle.integrate(delta);

    // Set new position after integrating
    Vector newPosition = ballParticle.getPosition();
    circleShape.setPosition(newPosition.x, newPosition.y);
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

real Ball::getRadius() const {
    return radius;
}

void Ball::changeColor(sf::Color color) {
    circleShape.setFillColor(color);
}

Particle* Ball::getParticle() {
    return &ballParticle;
}

void Ball::resolveScreenCollision(real WINDOW_WIDTH, real WINDOW_HEIGHT) {
    // Get the position and radius of the ball
    Vector position = ballParticle.getPosition();
    Vector velocity = ballParticle.getVelocity();

    // TODO: Implement more sophisticated way of detecting screen boundaries collisions
    // Check for collision with the left wall
    if (position.x - radius < 0) {
        if (velocity.x < 0.5f) {
            ballParticle.setVelocity(0.0f, velocity.y, velocity.z);
        } else {
            ballParticle.setVelocity(Vector(static_cast<real>(fabs(velocity.x)) * 0.6f, velocity.y, velocity.z));
        }
    }

    // Check for collision with the right wall
    if (position.x + radius > WINDOW_WIDTH) {
        ballParticle.setVelocity(Vector(static_cast<real>(-fabs(velocity.x)) * 0.6f, velocity.y, velocity.z));
    }

    // Check for collision with the top wall
    if (position.y - radius < 0) {
        if (velocity.y < 1.0f) {
            ballParticle.setVelocity(velocity.x, 0.0f, velocity.z);
        } else {
            ballParticle.setVelocity(Vector(velocity.x, static_cast<real>(fabs(velocity.y)) * 0.6f, velocity.z));
        }
        ballParticle.setVelocity(Vector(velocity.x, static_cast<real>(fabs(velocity.y)), velocity.z));
    }

    // Check for collision with the bottom wall
    if (position.y - radius > WINDOW_HEIGHT) {
        ballParticle.setVelocity(Vector(velocity.x, static_cast<real>(-fabs(velocity.y)) * 0.6f, velocity.z));
    }
}
