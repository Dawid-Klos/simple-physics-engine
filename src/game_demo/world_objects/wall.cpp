//
// Created by dave on 25.06.23.
//

#include "wall.h"

Wall::Wall(real width, real height, real posX, real posY, sf::Color color) {
    // Init shape properties
    shape.setFillColor(color);
    shape.setPosition(posX, posY);
    shape.setSize(sf::Vector2f(width, height));

    wallWidth = width;
    wallHeight = height;

    // Set bounding box based on width, height, posX and posY
    boundingBox.xMin = posX;
    boundingBox.xMax = posX + wallWidth;
    boundingBox.yMin = posY;
    boundingBox.yMax = posY + wallHeight;

    /** Set the Particle object properties for physics calculations */
    wallParticle.setPosition(posX, posY);
    wallParticle.setMass(0.0f);
    wallParticle.setDamping(0.0f);
    wallParticle.setVelocity(0.0f, 0.0f);
    wallParticle.setAcceleration(0.0f, 0.0f);
}

void Wall::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Wall::update(real delta) {
    // Perform integration
    //wallParticle.integrate(delta);

    // Set new position after integrating
    //Vector newPosition = wallParticle.getPosition();
//    shape.setPosition(wallParticle.getPosition().x, wallParticle.getPosition().y);
}

BoundingBox Wall::getBoundingBox() {
    return boundingBox;
}

Particle &Wall::getParticle() {
    return wallParticle;
}

bool Wall::collideWith(GameObject *other) {
    return collideWith(this);
}

bool Wall::collideWith(Ball *other) {
    // Ball properties
    real ballX = other->getParticle().getPosition().x;
    real ballY = other->getParticle().getPosition().y;
    real radius = other->getRadius();

    // Calculate the closest point between ball and rectangle
    real closestPointX = std::clamp(ballX, wallParticle.getPosition().x, wallWidth);
    real closestPointY = std::clamp(ballY, wallParticle.getPosition().y, wallHeight);

    // Calculate the distance between the closest point and the circle's center
    real distance = std::sqrt(real_pow(ballX - closestPointX, 2) +
                               real_pow(ballY - closestPointY, 2));

    // Check if the distance is less than or equal to the circle's radius
    return distance <= radius;
}

bool Wall::collideWith(Wall *other) {
    return false;
}

Wall::Wall() = default;
