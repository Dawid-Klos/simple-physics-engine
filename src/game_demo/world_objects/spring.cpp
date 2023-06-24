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

    /** Set line color */
    line[0].color = sf::Color(48,54,47);
    line[1].color = sf::Color(48,54,47);

    /** Set spring mass - SFML shape object properties */
    springMassShape.setRadius(springLength / 6);
    springMassShape.setFillColor(sf::Color(218, 116, 34));
    springMassShape.setOrigin(springLength / 6, springLength / 6);
    springMassShape.setPosition(anchorPos.x, anchorPos.y - springLength);

    /** Initialise Particle variables */
    springParticle.setMass(real(0.01) * springLength);
    springParticle.setDamping(0.99f);
    springParticle.setPosition(anchorPos.x, anchorPos.y - springLength);
}

Spring::~Spring() = default;

void Spring::draw(sf::RenderWindow &window) {
    window.draw(line, 2, sf::Lines);
    window.draw(springMassShape);
}

void Spring::update(real delta) {
    // Apply forces acting on the object
    calculateForces();

    // Perform integration
    springParticle.integrate(delta);
    Vector newPosition = springParticle.getPosition();

    // Set the line end position the same as the mass position
    line[1].position.x = newPosition.x;
    line[1].position.y = newPosition.y;

    springMassShape.setPosition(newPosition.x, newPosition.y);
}

void Spring::calculateForces() {
    gravityForce.updateForce(&springParticle);
    dragForce.updateForce(&springParticle);
    springForce.updateForce(&springParticle);
}

void Spring::extendSpring() {
    // Vector someForce = {0.0f, (-springParticle.getSpringRestLength() * 0.5f), 0.0f};
//    springParticle.setAcceleration(someForce);
}

void Spring::move(Vector acc) {
    springParticle.setAcceleration(acc);
}

Vector Spring::getCurrentAcceleration() {
    return springParticle.getAcceleration();
}

Vector Spring::getCurrentVelocity() {
    return springParticle.getVelocity();
}

Vector Spring::getCurrentPosition() {
    return springParticle.getPosition();
}
