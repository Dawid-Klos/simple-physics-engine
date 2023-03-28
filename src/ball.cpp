//
// Created by dave on 28.03.23.
//

#include "ball.h"

Ball::Ball(engine::real rad) {
    /** init variables */
    isPressed = false;
    radius = rad;

    /** init Particle variables */
    engine::Vector pos;
    circleParticle.getPosition(&pos);
    circleParticle.setMass(5.0f);
    circleParticle.setDamping(0.95f);

    /** set the Ball randomly in the scene */
    srand (static_cast <unsigned> (time(0)));
    auto x = static_cast <float> (rand() % 700);
    engine::real y = 500.0f;

    circleShape.setRadius(radius);
    circleShape.setFillColor(sf::Color::Magenta);

    circleShape.setPosition(x, y);
    circleParticle.setPosition(x, y, 0.0f);
}

Ball::~Ball() = default;

void Ball::setPressed(bool pressed) {
    isPressed = pressed;
}

void Ball::update(engine::real delta) {
    circleParticle.integrate(delta);

    engine::Vector newPosition = circleParticle.getPosition();
    circleShape.setPosition(newPosition.x, newPosition.y);
}

void Ball::draw(sf::RenderWindow &window) {
    window.draw(circleShape);
}

void Ball::move(engine::Vector acc) {
    circleParticle.setAcceleration(acc);
}

void Ball::jump() {
    engine::Vector jumpAcc = {0.0f, -15.0f, 0.0f};
    circleParticle.setAcceleration(jumpAcc);
}

