//
// Created by dave on 28.03.23.
//
#include "ball.h"

Ball::Ball(real rad, real posX, real posY) {
    // Init basic properties
    objectType = BALL;
    radius = rad;

    /** Set the Ball shape object properties and position in the simulation */
    circleShape.setRadius(radius);
    circleShape.setOrigin(radius, radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});
    circleShape.setPosition(posX, posY);

    /** Set the Particle object properties for physics calculations */
    setMass(real(0.15f) * rad);
    setDamping(0.98f);
    setPosition(posX, posY);
    setVelocity(15.0f * radius, 50.0f);
    setAcceleration(20.0f, 0.0f);
}

void Ball::update(real delta) {
    // Apply forces to the Ball
    calculateForces();

    // Check if the ball is on the ground and apply friction force
    if (getPosition().y + radius <= 25.0f) {
        frictionForce.updateForce(this);
    }

    // Perform integration
    integrate(delta);

    // Set new position after integrating
    Vector newPosition = getPosition();
    circleShape.setPosition(newPosition.x, newPosition.y);

    // Update ball bounding box with new position
    updateBoundingBox();
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}

void Ball::updateBoundingBox() {
    boundingBox.xMin = getPosition().x - radius;
    boundingBox.xMax = getPosition().x + radius;
    boundingBox.yMin = getPosition().y - radius;
    boundingBox.yMax = getPosition().y + radius;
}

void Ball::calculateForces() {
    gravityForce.updateForce(this);
    dragForce.updateForce(this);
}

void Ball::changeColor(sf::Color color) {
    circleShape.setFillColor(color);
}

BoundingBox Ball::getBoundingBox() const {
    return boundingBox;
}

Particle* Ball::getParticle() {
    return this;
}