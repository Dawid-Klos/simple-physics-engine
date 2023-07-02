//
// Created by dave on 01.07.23.
//

#include "box.h"

Box::Box(real width, real height, real posX, real posY) {
    // Init basic properties
    objectType = BOX;
    boxWidth = width;
    boxHeight = height;

    // Init shape properties
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width / 2.0f, height / 2.0f);
    shape.setFillColor(sf::Color{42, 157, 143});
    shape.setOutlineColor(sf::Color{38, 70, 83});
    shape.setOutlineThickness(2.0f);

    // Set bounding box based on width, height, posX and posY
    updateBoundingBox();

    // Set the Particle object properties for physics calculations
    setPosition(posX, posY);
    setMass(1.0f);
    setDamping(0.98f);
    setVelocity(0.0f, 0.0f);
    setAcceleration(0.0f, 0.0f);
}

void Box::draw(sf::RenderWindow &window) {
    window.draw(shape);

    // Reset color after drawing
    indicateCollision(sf::Color{38, 70, 83});
}

void Box::update(real delta) {
    // Apply forces to the Ball
    calculateForces();

    // Check if the ball is on the ground and apply friction force
    if (getPosition().y + boxHeight <= 50.0f) {
        frictionForce.updateForce(this);
    }

    // Perform integration
    integrate(delta);

    // Set new position after integrating
    Vector newPosition = getPosition();
    shape.setPosition(newPosition.x, newPosition.y);

    // Update ball bounding box with new position
    updateBoundingBox();
}

BoundingBox Box::getBoundingBox() const {
    return boundingBox;
}

Particle* Box::getParticle() {
    return this;
}

void Box::indicateCollision(sf::Color color) {
    shape.setOutlineColor(color);
}

void Box::calculateForces() {
    gravityForce.updateForce(this);
    dragForce.updateForce(this);
}

void Box::updateBoundingBox() {
    boundingBox.xMin = getPosition().x - boxWidth / 2;
    boundingBox.xMax = getPosition().x + boxWidth / 2;
    boundingBox.yMin = getPosition().y - boxHeight / 2;
    boundingBox.yMax = getPosition().y + boxHeight / 2;
}

Box::Box() = default;