//
// Created by dave on 28.03.23.
//

#include "ball.h"

Ball::Ball(engine::real rad) {
    /** init variables */
    radius = rad;

    /** init Particle variables */
    engine::Vector pos;
    this->getPosition(&pos);
    this->setMass(5.0f);
    this->setDamping(0.90f);
    // this->setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
    // this->setAcceleration(0.0f, -20.0f, 0.0f);

    /** set the Ball randomly in the scene */
    srand (static_cast <unsigned> (time(0)));
    auto x = static_cast <float> (rand() % 700);
    engine::real y = 120.0f;

    circleShape.setRadius(radius);
    circleShape.setFillColor(sf::Color{169, 151, 223});

    circleShape.setPosition(x, y);
    this->setPosition(x, y, 0.0f);
}

Ball::~Ball() = default;

void Ball::update(engine::real delta, sf::Window &window) {
    this->integrate(delta);
    engine::Vector newPosition = this->getPosition();

    // temp
    if (newPosition.y < 0.0f) {
        newPosition.y = 0.0f;
    }

    // fix conventional coordinates system into screen coordinates system
    circleShape.setPosition(newPosition.x, window.getPosition().y - newPosition.y);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}

void Ball::move(engine::Vector acc) {
    this->setAcceleration(acc);
    // this->setStoredForce(acc);
}

void Ball::jump() {
    engine::Vector jumpAcc = {0.0f, 15.0f, 0.0f};
    this->setAcceleration(jumpAcc);
}
engine::Vector Ball::getAcceleration() {
    return this->acceleration;
}

engine::Vector Ball::getVelocity() {
    return this->velocity;
}

engine::Vector Ball::getCurrentPosition() {
    return this->position;
}

