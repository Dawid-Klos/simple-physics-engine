//
// Created by dave on 13.05.23.
//
#include "simulation_renderer.h"

SimulationRenderer::SimulationRenderer(real width, real height) {
    // Initialize screen size
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    // Enable anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Initialize new window object
    window = new sf::RenderWindow(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Physics Simulation", sf::Style::Default, settings);

    // Set limit for frames-per-second in simulation
    unsigned int fps = 60;
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
    worldInfo.setPosition(50.0f, WINDOW_HEIGHT - 50.0f);
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

sf::RenderWindow *SimulationRenderer::getWindow() const {
    return window;
}

unsigned int SimulationRenderer::getCollisionsCount() const {
    return collisionsCount;
}

void SimulationRenderer::update(const vector<GameObject*>& myObjects) {
    // Update delta time
    delta = clock.restart().asSeconds() * 5.0f;

    // Create sub-steps for collision detection
    real dt_sub = delta / 8.0f;

    for (int i = 0; i < 8; i++) {
        // Collision detection
        collisionDetector.detectCollisions();
        collisionResolver.resolve();

        collisionsCount = collisionResolver.getCollisionsSize();
        collisionResolver.removeResolvedCollisions();

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
    }

    // Draw text
    window->draw(worldInfo);

    // Display new frame
    window->display();
}