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
    unsigned int fps = 80;
    window->setFramerateLimit(fps);

    // Set up window View - reverse window height coordinates
    sf::View view = window->getDefaultView();
    view.setSize(WINDOW_WIDTH, -WINDOW_HEIGHT);
    window->setView(view);

    // Set up font/text
    myFont.loadFromFile("../assets/Roboto-Medium.ttf");
    worldInfo.setFont(myFont);
    worldInfo.setFillColor(sf::Color(48,54,47));
    worldInfo.setCharacterSize(18);
    worldInfo.setPosition(10.0f , WINDOW_HEIGHT * 0.2f);
    worldInfo.setScale(1.0, -1.0);
}

SimulationRenderer::~SimulationRenderer() {
    delete this->window;
}

bool SimulationRenderer::running() const {
    return window->isOpen();
}

void SimulationRenderer::addObjectToDetector(GameObject* gameObject) {
    collisionDetector.addObject(gameObject);
}

void SimulationRenderer::drawText(const sf::String &str) {
    worldInfo.setString(str);
}

void SimulationRenderer::updateEvents(const vector<GameObject*>& myObjects) {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    myObjects[0]->getParticle()->setAcceleration(Vector(0.0f, -80.0f));
                }
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left) {
                    myObjects[0]->getParticle()->setAcceleration(Vector(-80.0f, 0.0f));
                    break;
                } else if (event.key.code == sf::Keyboard::Right) {
                    myObjects[0]->getParticle()->setAcceleration(Vector(80.0f, 0.0f));
                    break;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    myObjects[0]->getParticle()->setAcceleration(Vector(0.0f, -80.0f));
                    break;
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

    // Create sub-steps for collision detection
    real dt_sub = delta / 8.0f;

    for (int i = 0; i < 8; i++) {
        // Collision detection
        collisionDetector.detectCollisions();
        collisionResolver.resolve();

        // Update particle position
        for (auto* object : myObjects) {
            object->update(dt_sub);
        }
    }
}

void SimulationRenderer::render(const vector<GameObject*>& myObjects) {
    // Clear the window
    window->clear(sf::Color(255, 251, 219));

    // Draw the objects
    for (auto* object : myObjects) {
        object->draw(*window);

        // Reset the color of the balls
        object->changeColor(sf::Color{169, 151, 223});
    }

    // Draw text
    window->draw(worldInfo);

    // Display new frame
    window->display();
}