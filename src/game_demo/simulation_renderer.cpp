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

    // Initialize new window object
    window = new sf::RenderWindow(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Physics Simulation", sf::Style::Default, settings);

    // Set FPS limit
    unsigned int fps = 100;
    window->setFramerateLimit(fps);

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

void SimulationRenderer::updateEvents(const vector<GameObject*>& myObjects) {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left) {

                } else if (event.key.code == sf::Keyboard::Right) {

                } else if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                } else if (event.key.code == sf::Keyboard::Space) {

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
     updateEvents(myObjects);

    // Reset the color of the balls after collisions resolved
//    for (auto* object : myObjects) {
//        object->changeColor(sf::Color{169, 151, 223});
//    }

    real dt_sub = delta / 4.0f;

    for (int i = 0; i < 4; i++) {
        // Collision detection
        collisionDetector.detectCollisions();
        collisionResolver.resolve();

        // Update particle position
        for (auto* object : myObjects) {
            object->update(dt_sub);
        }
    }

//    // Collision detection
//    collisionDetector.detectCollisions();
//    collisionResolver.resolve();
//
//    // Update particle position
//    for (auto* object : myObjects) {
//        object->update(delta);
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