//
// Created by dave on 14.04.23.
//

#include "spring.h"

Spring::Spring(real springLength) {
    /** Set spring line position */
    line[0] = sf::Vector2f(400.0f, 0.0f);
    line[1] = sf::Vector2f(400.0f, 600.0f - springLength);
    point[0] = sf::Vector2f(400.0f, 600.0f - springLength);

    /** Set line color */
    line[0].color = sf::Color(48,54,47);
    line[1].color = sf::Color(48,54,47);
    point[0].color = sf::Color(218, 116, 34);

    /** Set spring mass */
    springMass.setRadius(springLength / 6);
    springMass.setFillColor(sf::Color(218, 116, 34));
    springMass.setOrigin(springLength / 6, springLength / 6);
    springMass.setPosition(400.0f, 600.0f - springLength);

    /** Initialise Particle variables */
    Vector originPosition = {line[0].position.x, line[0].position.y, 0.0f};
    springParticle.setSpringOriginPosition(originPosition);
    springParticle.setSpringRestLength(springLength);
    springParticle.setMass(real(0.01) * springLength);
    springParticle.setDamping(0.99f);
    springParticle.setPosition(400.0f, 600.0f - springLength, 0.0f);

    springParticle.setVelocity(0.0f, 0.0f, 0.0f);
    springParticle.setAcceleration(0.0f, 0.0f, 0.0f);
}

Spring::~Spring() = default;

void Spring::draw(sf::RenderWindow &window) {
    window.draw(line, 2, sf::Lines);
    window.draw(point, 1, sf::Points);
    window.draw(springMass);
}

void Spring::update(real delta, sf::Window &window) {
    // Apply forces acting on the object
    calculateForces();

    // Perform integration
    springParticle.integrate(delta);
    Vector newPosition = springParticle.getPosition();

    // Set the line end position the same as the mass position
    line[1].position.x = newPosition.x;
    line[1].position.y = real(window.getPosition().y) - newPosition.y;

    // Fix conventional coordinates system into screen coordinates system
    springMass.setPosition(newPosition.x, real(window.getPosition().y) - newPosition.y);
}

void Spring::calculateForces() {
    gravityForce.updateForce(&springParticle);
    dragForce.updateForce(&springParticle);
    springForce.updateForce(&springParticle);
}

void Spring::extendSpring() {
    Vector someForce = {0.0f, (-springParticle.getSpringRestLength() * 0.5f), 0.0f};
    springParticle.setAcceleration(someForce);
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
