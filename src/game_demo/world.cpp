//
// Created by dave on 11.05.23.
//

#include "world.h"

void World::setScreenBoundaries(real window_width, real window_height) {
    // Screen - left wall
    screen.leftWall = new Wall(1.0f, window_height, -1.0f, 0.0f, sf::Color::Black);
    worldObjects.push_back(screen.leftWall);
    renderer->addObjectToDetector(screen.leftWall);

    // Screen - right wall
    screen.rightWall = new Wall(1.0f, window_height, window_width, 0.0f, sf::Color::Black);
    worldObjects.push_back(screen.rightWall);
    renderer->addObjectToDetector(screen.rightWall);

    // Screen - bottom wall
    screen.bottomWall = new Wall(window_width, 1.0f, 0.0f, 0.0f, sf::Color::Red);
    screen.bottomWall->objectType = FLOOR;
    worldObjects.push_back(screen.bottomWall);
    renderer->addObjectToDetector(screen.bottomWall);

    // Screen - top wall
    screen.topWall = new Wall(window_width, 1.0f, 0.0f, window_height, sf::Color::Green);
    worldObjects.push_back(screen.topWall);
    renderer->addObjectToDetector(screen.topWall);
}

void World::createBall() {
    if (ballsTimer >= 100) return;

    GameObject* ball = new Ball(10.0f, 100.0f, 1000.0f);

    worldObjects.push_back(ball);
    renderer->addObjectToDetector(ball);

    ballsTimer += 1;
}

void World::createSpringSystem(real WINDOW_WIDTH, real WINDOW_HEIGHT) {
    spring = new Spring(80.0f, {WINDOW_WIDTH, WINDOW_HEIGHT});
    worldObjects.push_back(spring);
    renderer->addObjectToDetector(spring);
}

void World::updateSpringSystemInfo() {
    // Print information on screen about the Spring object
    Vector velocity =  spring->getCurrentVelocity();
    Vector position =  spring->getCurrentPosition();

    ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
    ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;
    ss << "Objects count: " << worldObjects.size() << std::endl;
}

void World::update() {
    if (spring != nullptr) {
        updateSpringSystemInfo();
    }

    renderer->drawText(ss.str());
    ss.str(std::string());

    renderer->updateEvents(worldObjects);
    renderer->update(worldObjects);
    renderer->render(worldObjects);
}
