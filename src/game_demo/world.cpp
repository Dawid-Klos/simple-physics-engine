//
// Created by dave on 11.05.23.
//

#include "world.h"

void World::setScreenBoundaries(real window_width, real window_height) {
    // Screen - left wall
    screen.leftWall = new Wall(10.0f, window_height, 0.0f, 0.0f, sf::Color::Black);
    worldObjects.push_back(screen.leftWall);
    renderer->addObjectToDetector(screen.leftWall);

    // Screen - right wall
    screen.rightWall = new Wall(10.0f, window_height, window_width - 10.0f, 0.0f, sf::Color::Black);
    worldObjects.push_back(screen.rightWall);
    renderer->addObjectToDetector(screen.rightWall);

    // Screen - bottom wall
    screen.bottomWall = new Wall(window_width, 10.0f, 0.0f, 0.0f, sf::Color::Red);
    worldObjects.push_back(screen.bottomWall);
    renderer->addObjectToDetector(screen.bottomWall);

    // Screen - top wall
    screen.topWall = new Wall(window_width, 10.0f, 0.0f, window_height - 10.0f, sf::Color::Green);
    worldObjects.push_back(screen.topWall);
    renderer->addObjectToDetector(screen.topWall);
}

void World::createBall() {
    if (ballsTimer > 200) return;

    GameObject* ball = new Ball(10.f, 100.0f, 500.0f);

    worldObjects.push_back(ball);
    renderer->addObjectToDetector(ball);

    ballsTimer += 1;
}

void World::createSpringSystem(real WINDOW_HEIGHT) {
//    spring = Spring(50.0f, WINDOW_HEIGHT);
}

void World::updateSpringSystemInfo() {
    // Print information on screen about the Spring
//    Vector acceleration = spring.getCurrentAcceleration();
//    Vector velocity =  spring.getCurrentVelocity();
//    Vector position =  spring.getCurrentPosition();
//
//    ss << "Acc = x: " << acceleration.x << "  y: " << acceleration.y << std::endl;
//    ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
//    ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;
}

void World::update() {
    updateSpringSystemInfo();

    renderer->drawText(ss.str());
    ss.str(std::string());

//    renderer->updateEvents(spring);
    renderer->update(worldObjects);
    renderer->render(worldObjects);
}
