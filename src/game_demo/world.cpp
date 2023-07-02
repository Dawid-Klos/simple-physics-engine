//
// Created by dave on 11.05.23.
//

#include "world.h"
#include "world_objects/ball.h"
#include "world_objects/wall.h"
#include "world_objects/spring.h"
#include "world_objects/box.h"

void World::setScreenBoundaries(real window_width, real window_height) {
    // Screen - left wall
    screen.leftWall = new Wall(10.0f, window_height - 30.0f, 20.0f, window_height / 2.0f -20.0f);
    worldObjects.push_back(screen.leftWall);
    renderer->addObjectToDetector(screen.leftWall);

    // Screen - right wall
    screen.rightWall = new Wall(10.0f, window_height - 40.0f, window_width - 20.0f, window_height / 2.0f - 20.0f);
    worldObjects.push_back(screen.rightWall);
    renderer->addObjectToDetector(screen.rightWall);

    // Screen - floor
    screen.bottomWall = new Wall(window_width - 30.0f, 10.0f, window_width / 2.0f, 0.0f);
    screen.bottomWall->objectType = FLOOR;
    worldObjects.push_back(screen.bottomWall);
    renderer->addObjectToDetector(screen.bottomWall);

    // Screen - ceiling
    screen.topWall = new Wall(window_width - 30.0f, 10.0f, window_width / 2.0f, window_height - 40.0f);
    worldObjects.push_back(screen.topWall);
    renderer->addObjectToDetector(screen.topWall);
}

void World::createBall() {
    if (ballsTimer >= 100) return;

    GameObject* ball = new Ball(15.0f, 125.0f, 800.0f);
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

    ss << "Spring system:\n" << std::endl;
    ss << "--> Velocity   x: " << velocity.x << "  y: " << velocity.y << std::endl;
    ss << "--> Position   x: " << position.x << "  y: " << position.y << std::endl;
    ss << "\n\n" << std::endl;
    ss << "World information:\n" << std::endl;
    ss << "--> Number of objects:   " << worldObjects.size() << std::endl;
    ss << "--> Number of collisions:   " << renderer->getCollisionsCount() << std::endl;
}

void World::update() {
    if (spring != nullptr) {
        updateSpringSystemInfo();
    }

    renderer->drawText(ss.str());
    ss.str(std::string());

    processInput();
    renderer->update(worldObjects);
    renderer->render(worldObjects);
}

void World::processInput() {

    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // get mouse position
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                    GameObject* box = new Box(40.0f, 40.0f, real(mousePosition.x), real(mousePosition.y));
                    worldObjects.push_back(box);
                    renderer->addObjectToDetector(box);
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    // get mouse position
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                    GameObject* ball = new Ball(15.0f, real(mousePosition.x), real(mousePosition.y));
                    worldObjects.push_back(ball);
                    renderer->addObjectToDetector(ball);
                }
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left) {
                    worldObjects[0]->getParticle()->setAcceleration(Vector(-80.0f, 0.0f));
                    break;
                } else if (event.key.code == sf::Keyboard::Right) {
                    worldObjects[0]->getParticle()->setAcceleration(Vector(80.0f, 0.0f));
                    break;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    worldObjects[0]->getParticle()->setAcceleration(Vector(0.0f, -80.0f));
                    break;
                } else if (event.key.code == sf::Keyboard::G) {
                    // remove gravity for each object
                    for (auto &worldObject : worldObjects) {
                        worldObject->getParticle()->addForce(Vector(0.0f, 100.0f));
                    }
                    break;
                }
                break;
            default:
                break;
        }
    }
}
