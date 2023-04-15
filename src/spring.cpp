//
// Created by dave on 14.04.23.
//

#include "spring.h"

Spring::Spring(engine::real springLength) {
    /** Init spring variables */
    restLength = springLength;
    initSpringForce();

    /** Set spring lines position */
    line[0] = sf::Vector2f(400.0f, 0.0f);
    line[1] = sf::Vector2f(400.0f, 600.0f - springLength);

    /** Set lines color */
    line[0].color = sf::Color(48,54,47);
    line[1].color = sf::Color(48,54,47);

    /** Set spring mass  */
    springMass.setRadius(springLength / 6);
    springMass.setFillColor(sf::Color(218, 116, 34));
    springMass.setOrigin(springLength / 6, springLength / 6);
    springMass.setPosition(400.0f, 600.0f - springLength);

    /** Initialise Particle variables */
    this->setMass(engine::real(0.01) * springLength);
    this->setDamping(0.95f);
    this->setPosition(400.0f, 600.0f - springLength, 0.0f);
}

Spring::~Spring() = default;

void Spring::draw(sf::RenderWindow &window) {
    window.draw(line, 2, sf::Lines);
    window.draw(springMass);
}

void Spring::update(engine::real delta, sf::Window &window) {
    // Add spring force before integration
    engine::Vector storedSpringForce;
    springForce.updateForce(storedSpringForce);
    this->addForce(storedSpringForce);

    this->integrate(delta);
    engine::Vector newPosition = this->getPosition();

    // fix conventional coordinates system into screen coordinates system
    line[1].position.x = newPosition.x;
    line[1].position.y = engine::real(window.getPosition().y) - newPosition.y;
    springMass.setPosition(newPosition.x, engine::real(window.getPosition().y) - newPosition.y);
}

void Spring::initSpringForce() {
    engine::Vector originPosition = {line[0].position.x, line[0].position.y, 0.0f};
    engine::Vector otherEndPosition = getPosition();
    springForce.getSpringAttributes(originPosition, otherEndPosition, restLength);
}

engine::Vector Spring::getCurrentAcceleration() {
    return this->getAcceleration();
}

engine::Vector Spring::getCurrentVelocity() {
    return this->getVelocity();
}

engine::Vector Spring::getCurrentPosition() {
    return this->getPosition();
}

void Spring::extendSpring() {
    engine::Vector someForce = {0.0f, -25.0f, 0.0f};
    this->setAcceleration(someForce);
}

void Spring::move(engine::Vector acc) {
    this->setAcceleration(acc);
}

