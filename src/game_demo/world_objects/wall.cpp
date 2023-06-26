//
// Created by dave on 25.06.23.
//

#include "wall.h"

Wall::Wall(real width, real height, real posX, real posY, sf::Color color) {
    // Init basic properties
    objectType = WALL;
    wallWidth = width;
    wallHeight = height;

    // Init shape properties
    shape.setFillColor(color);
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(width, height));

    // Set bounding box based on width, height, posX and posY
    boundingBox.xMin = posX;
    boundingBox.xMax = posX + wallWidth;
    boundingBox.yMin = posY;
    boundingBox.yMax = posY + wallHeight;

    // Set the Particle object properties for physics calculations
    this->setPosition(posX, posY);
    this->setMass(0.0f);
    this->setDamping(0.99f);
    this->setVelocity(0.0f, 0.0f);
    this->setAcceleration(0.0f, 0.0f);
}

void Wall::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Wall::update(real delta) {
    // Perform integration
    integrate(delta);

    // Set new position after integrating
    shape.setPosition(getPosition().x, getPosition().y);

    // Update bounding box
    updateBoundingBox();
}

real Wall::getWidth() const {
    return wallWidth;
}

real Wall::getHeight() const {
    return wallHeight;
}

BoundingBox Wall::getBoundingBox() const {
    return boundingBox;
}

Particle* Wall::getParticle() {
    return this;
}

void Wall::updateBoundingBox() {
    boundingBox.xMin = getPosition().x;
    boundingBox.xMax = getPosition().x + wallWidth;
    boundingBox.yMin = getPosition().y;
    boundingBox.yMax = getPosition().y + wallHeight;
}

Wall::Wall() = default;
