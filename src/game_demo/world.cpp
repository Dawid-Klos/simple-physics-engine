//
// Created by dave on 11.05.23.
//

#include <iostream>
#include "world.h"

void World::createBalls() {
    real delta = renderer->getDelta();

    if (ballsTimer < 100) {
        Ball* ball = new Ball(100.0f * delta, 20.0f * float(ballsTimer), 5.0f * float(ballsTimer));
        myBalls.push_back(ball);
        renderer->addObjectToDetector(ball);
        ballsTimer += 1;
        std::cout << "Balls: " << myBalls.size() << std::endl;
    }
}

void World::createSpringSystem(real WINDOW_HEIGHT) {
    spring = Spring(50.0f, WINDOW_HEIGHT);
}

void World::updateSpringSystemInfo() {
    // Print information on screen about the Spring
    Vector acceleration = spring.getCurrentAcceleration();
    Vector velocity =  spring.getCurrentVelocity();
    Vector position =  spring.getCurrentPosition();
    ss << "Acc = x: " << acceleration.x << "  y: " << acceleration.y << std::endl;
    ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
    ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;
}

void World::update() {
    updateSpringSystemInfo();

    renderer->drawText(ss.str());
    ss.str(std::string());

    renderer->update(myBalls, spring);
    renderer->render(myBalls, spring);
}