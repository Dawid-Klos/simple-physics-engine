//
// Created by dave on 13.05.23.
//

#include <iostream>
#include "simulation_renderer.h"

SimulationRenderer::SimulationRenderer(real width, real height) {
    // Init screen size
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    // enable anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window = new sf::RenderWindow(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Physics Simulation", sf::Style::Default, settings);

    // Set up window View - reverse window height coordinates
    sf::View view = window->getDefaultView();
    view.setSize(WINDOW_WIDTH, -WINDOW_HEIGHT);
    window->setView(view);
}

SimulationRenderer::~SimulationRenderer() {
    delete this->window;
}

void SimulationRenderer::addObjectToDetector(GameObject* gameObject) {
    collisionDetector.addObject(gameObject);
}

void SimulationRenderer::drawText(const sf::String &str) {
    myFont.loadFromFile("../assets/Roboto-Medium.ttf");
    myText.setFont(myFont);
    myText.setFillColor(sf::Color(48,54,47));
    myText.setString(str);
    myText.setCharacterSize(24);
    myText.setPosition(10.0f, WINDOW_HEIGHT - 10.0f);
    myText.setScale(1.0, -1.0);
}

bool SimulationRenderer::running() const {
    return window->isOpen();
}

void SimulationRenderer::updateEvents(Spring &spring) {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left) {
                    spring.move(Vector(-45.0f, 0.0f));
                } else if (event.key.code == sf::Keyboard::Right) {
                    spring.move(Vector(45.0f, 0.0f));
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    spring.extendSpring();
                }
                break;
            default:
                break;
        }
    }
}

void SimulationRenderer::update(const vector<GameObject*>& myObjects) {
    // Update delta time
    delta = clock.restart().asSeconds() * 5.0f;

    // Update pool events
//     updateEvents(spring);

    // Reset the color of the balls after collisions resolved
    for (auto* object : myObjects) {
//        object->changeColor(sf::Color{169, 151, 223});
    }

    // Collision detection
    collisionDetector.detectCollisions();

    // Update particle position
    for (auto* object : myObjects) {
        object->update(delta);
    }


    // Temp solution for screen collisions
//    for (auto* object : myObjects) {
//        ball->resolveScreenCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
//    }
}

void SimulationRenderer::render(const vector<GameObject*>& myObjects) {
    // Clear the window
    window->clear(sf::Color(255, 251, 219));

    // Draw the objects
    for (auto* object : myObjects) {
        object->draw(*window);
    }

    // Draw text
    window->draw(myText);

    // Display new frame
    window->display();
}

sf::RenderWindow* SimulationRenderer::getWindow() const {
    return window;
}

real SimulationRenderer::getDelta() const {
    return delta;
}
