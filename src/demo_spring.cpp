//
// Created by dave on 14.04.23.
//
#include <engine/vector.h>

#include <SFML/Graphics.hpp>
#include "spring.h"

using namespace engine;

int drawLine() {
    // enable anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    auto const width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Physics Simulation", sf::Style::Default, settings);

    unsigned int fps = 80;
    window.setFramerateLimit(fps);

    // Clock and text
    sf::Clock clock;
    engine::real delta;

    // Objects
    Spring spring = Spring(50.0f);

    while (window.isOpen()) {

        delta = clock.restart().asSeconds() + 0.035f;
        sf::Event event{};

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    break;
                default:
                    break;
            }
        }

//        Vector bounds = spring.getGloibal
//        ss << "Acc = x: " << acceleration.x << "  y: " << acceleration.y << std::endl;
//        ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
//        ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;

        // Update particle position
        spring.update(delta, window);

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the ball
        spring.draw(window);

        // End of frame
        window.display();
    }
    return 0;
}