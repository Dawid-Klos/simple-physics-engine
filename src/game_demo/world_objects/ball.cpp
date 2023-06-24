//
// Created by dave on 28.03.23.
//
#include "ball.h"

Ball::Ball(real rad, real posX, real posY) {
    /** Initialise variables */
    radius = rad;

    /** Set the Ball shape object properties and position in the simulation */
    circleShape.setRadius(radius);
    circleShape.setOrigin(radius, radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});
    circleShape.setPosition(posX, posY);

    /** Set the Particle object properties for physics calculations */
    ballParticle.setMass(real(0.15f) * rad);
    ballParticle.setDamping(0.95f);
    ballParticle.setPosition(posX, posY);
    ballParticle.setVelocity(60.0f, 50.0f);
    ballParticle.setAcceleration(20.0f, 0.0f);
}

Ball::~Ball() = default;

void Ball::update(real delta) {
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

Ball::BoundingBox Ball::getBoundingBox() const {
    return boundingBox;
}

void Ball::updateBoundingBox() {
    boundingBox.xMin = ballParticle.getPosition().x - radius;
    boundingBox.xMax = ballParticle.getPosition().x + radius;
    boundingBox.yMin = ballParticle.getPosition().y - radius;
    boundingBox.yMax = ballParticle.getPosition().y + radius;
}

void Ball::calculateForces() {
    gravityForce.updateForce(&ballParticle);
    dragForce.updateForce(&ballParticle);
}

void Ball::move(Vector acc) {
    ballParticle.setAcceleration(acc);
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
    if (position.x + radius < 0.0f) {
        if (velocity.x < 0.5f) {
            ballParticle.setVelocity(0.0f, velocity.y);
        } else {
            ballParticle.setVelocity(Vector(static_cast<real>(fabs(velocity.x)) * 0.1f, velocity.y));
        }
    }

    // Check for collision with the right wall
    if (position.x + radius > WINDOW_WIDTH) {
        ballParticle.setVelocity(Vector(static_cast<real>(-fabs(velocity.x)) * 0.1f, velocity.y));
    }

    // Check for collision with the bottom wall - floor
    if (position.y - radius < 0.0f) {
        if (velocity.y < 0.0f && velocity.y > - 0.5f) {
            ballParticle.setVelocity(Vector(velocity.x, 0.0f));
        } else {
            ballParticle.setVelocity(Vector(velocity.x, static_cast<real>(fabs(velocity.y)) * 0.6f));
        }
    }

    // Check for collision with the top wall
    if (position.y - radius > WINDOW_HEIGHT) {
         ballParticle.setVelocity(Vector(velocity.x, static_cast<real>(-fabs(velocity.y)) * 0.6f));
    }
}
