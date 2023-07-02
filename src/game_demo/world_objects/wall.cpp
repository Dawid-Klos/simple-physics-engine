//
// Created by dave on 25.06.23.
//

#include "wall.h"

Wall::Wall(real width, real height, real posX, real posY) {
    // Init basic properties
    objectType = WALL;
    wallWidth = width;
    wallHeight = height;

    // Init shape properties
    shape.setFillColor(sf::Color{231, 111, 81});
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width / 2.0f, height / 2.0f);

    // Set bounding box based on width, height, posX and posY
    boundingBox.xMin = posX - wallWidth / 2.0f;
    boundingBox.xMax = posX + wallWidth / 2.0f;
    boundingBox.yMin = posY - wallHeight / 2.0f;
    boundingBox.yMax = posY + wallHeight / 2.0f;

    // Set the Particle object properties for physics calculations
    setPosition(posX, posY);
    setMass(0.0f);
    setDamping(0.99f);
    setVelocity(0.0f, 0.0f);
    setAcceleration(0.0f, 0.0f);
}

void Wall::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Wall::update(real delta) {
    // Reset color
    indicateCollision(sf::Color{231, 111, 81});
    // Static object, no update needed
}

BoundingBox Wall::getBoundingBox() const {
    return boundingBox;
}

Particle* Wall::getParticle() {
    return this;
}

void Wall::indicateCollision(sf::Color color) {
    shape.setOutlineColor(color);
}

Wall::Wall() = default;