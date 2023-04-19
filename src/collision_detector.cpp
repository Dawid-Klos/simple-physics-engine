//
// Created by dave on 17.04.23.
//
#include "engine/collision_detector.h"
#include "ball.h"
#include <iostream>
using namespace engine;

void CollisionDetector::addBall(Ball* ball) {
    balls.push_back(ball);
}

void CollisionDetector::checkForCollision(Ball& ball1, Ball& ball2) {
    Particle* particle1 = ball1.getParticle();
    Particle* particle2 = ball2.getParticle();

    real radiusSum = ball1.getRadius() + ball2.getRadius();
    Vector distance = particle2->getPosition() - particle1->getPosition();
    real distanceMagnitude = distance.getMagnitude();

    if (distanceMagnitude < radiusSum) {
        ball1.changeColor(sf::Color{9, 151, 223});
        ball2.changeColor(sf::Color{9, 151, 223});
        collisionResolver.addCollision(particle1, particle2);
        std::cout << "collision added" << std::endl;
    }
}

void CollisionDetector::detectCollisions() {
    // detect collisions between all pairs of balls
    for (size_t i = 0; i < balls.size(); i++) {
        Ball& ball1 = *balls[i];
        for (size_t j = i + 1; j < balls.size(); j++) {
            Ball& ball2 = *balls[j];
            if (ballsOverlap(ball1, ball2)) {
                ball1.changeColor(sf::Color{9, 151, 223});
                ball2.changeColor(sf::Color{9, 151, 223});
                collisions += 1;
                collisionResolver.addCollision(ball1.getParticle(), ball2.getParticle());
            }
        }
    }
}

bool CollisionDetector::ballsOverlap(Ball &ball1, Ball &ball2)  {
    const real radiusSum = ball1.getRadius() + ball2.getRadius();
    const Vector distance = ball2.getParticle()->getPosition() - ball1.getParticle()->getPosition();
    const real distanceMagnitude = distance.getMagnitude();
    // add small threshold to radius sum to reduce false collisions
    return distanceMagnitude < (radiusSum + 0.001);
}

