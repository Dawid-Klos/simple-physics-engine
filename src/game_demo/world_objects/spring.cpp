//
// Created by dave on 14.04.23.
//

#include "spring.h"

Spring::Spring(real len, Vector anchorPos) {
    /** Set spring line position - line[0] anchor - line[1] end */
    line[0] = sf::Vector2f(anchorPos.x, anchorPos.y);
    line[1] = sf::Vector2f(anchorPos.x, anchorPos.y - springLength);

    /** Store spring length in rest */
    springLength = len;

    /** Initialize spring force system */
    springForce.initSpringParameters(springLength, anchorPos);
    objectType = SPRING;

    /** Set line color */
    line[0].color = sf::Color(48,54,47);
    line[1].color = sf::Color(48,54,47);

    /** Set spring mass - SFML shape object properties */
    springMassShape.setRadius(springLength / 6);
    springMassShape.setFillColor(sf::Color(218, 116, 34));
    springMassShape.setOrigin(springLength / 6, springLength / 6);
    springMassShape.setPosition(anchorPos.x, anchorPos.y - springLength);

    /** Initialise Particle variables */
    setMass(real(0.005) * springLength);
    setDamping(0.90f);
    setVelocity(0.0f, 0.0f);
    setPosition(anchorPos.x, anchorPos.y - springLength);
}

void Spring::draw(sf::RenderWindow &window) {
    window.draw(line, 2, sf::Lines);
    window.draw(springMassShape);
}

void Spring::update(real delta) {
    // Apply forces acting on the object
    calculateForces();

    // Perform integration
    integrate(delta);
    Vector newPosition = getPosition();

    // Set the line end position the same as the mass position
    line[1].position.x = newPosition.x;
    line[1].position.y = newPosition.y;
    springMassShape.setPosition(newPosition.x, newPosition.y);

    updateBoundingBox();
}

void Spring::calculateForces() {
    gravityForce.updateForce(this);
    dragForce.updateForce(this);
    springForce.updateForce(this);
}

void Spring::extendSpring() {
    // Vector someForce = {0.0f, (-springParticle.getSpringRestLength() * 0.5f), 0.0f};
//    springParticle.setAcceleration(someForce);
}

void Spring::move(Vector acc) {
    setAcceleration(acc);
}

Vector Spring::getCurrentAcceleration() {
    return getAcceleration();
}

Vector Spring::getCurrentVelocity() {
    return getVelocity();
}

Vector Spring::getCurrentPosition() {
    return getPosition();
}

Particle* Spring::getParticle() {
    return this;
}

BoundingBox Spring::getBoundingBox() const {
    return boundingBox;
}

void Spring::updateBoundingBox() {
    boundingBox.xMin = getPosition().x - springLength / 6;
    boundingBox.xMax = getPosition().x + springLength / 6;
    boundingBox.yMin = getPosition().y - springLength / 6;
    boundingBox.yMax = getPosition().y + springLength / 6;
}

void Spring::changeColor(sf::Color color) {
    springMassShape.setFillColor(color);
}
