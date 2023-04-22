//
// Created by dave on 17.04.23.
//
#include "engine/collision_detector.h"
#include "ball.h"
using namespace engine;

void CollisionDetector::addBall(Ball* ball) {
    balls.push_back(ball);
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
    return distanceMagnitude < (radiusSum + 0.01);
}

