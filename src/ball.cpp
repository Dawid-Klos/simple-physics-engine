//
// Created by dave on 28.03.23.
//

#include "ball.h"

Ball::Ball(engine::real rad) {
    /** init variables */
    radius = rad;

    /** init Particle variables */
//    engine::Vector pos;
//    this->getPosition(&pos);
    this->setMass(engine::real(1.2) * rad);
    this->setDamping(0.95f);
    this->setVelocity(0.0f, 5.0f, 0.0f);
    this->setAcceleration(0.0f, -5.0f, 0.0f);

    /** set the Ball randomly in the scene */
    srand (static_cast <unsigned> (time(0)));
    auto x = static_cast <float> (rand() % 700);
    x += engine::real(1.555) * rad;
    engine::real y = 150.0f;

    circleShape.setRadius(radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});

    circleShape.setPosition(x, y);
    this->setPosition(x, y, 0.0f);
}

Ball::~Ball() = default;

void Ball::update(engine::real delta, sf::Window &window) {
    this->integrate(delta);

    engine::Vector newPosition = this->getPosition();

    // fix conventional coordinates system into screen coordinates system
    circleShape.setPosition(newPosition.x, engine::real(window.getPosition().y) - newPosition.y);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}

void Ball::move(engine::Vector acc) {
    this->setAcceleration(acc);
}

void Ball::jump() {
    engine::Vector jumpAcc = {0.0f, 100.0f, 0.0f};
    this->setAcceleration(jumpAcc);
}
engine::Vector Ball::getCurrentAcceleration() {
    return this->getAcceleration();
}

engine::Vector Ball::getCurrentVelocity() {
    return this->getVelocity();
}

engine::Vector Ball::getCurrentPosition() {
    return this->getPosition();
}

