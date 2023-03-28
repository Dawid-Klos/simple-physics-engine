#include <iostream>
#include <engine/vector.h>
#include <engine/particle.h>

#include <SFML/Graphics.hpp>
#include <ball.h>


using namespace engine;

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Simulation");
    sf::Clock clock;
    Ball ball = Ball(50.0f);


    sf::RectangleShape floor;
    floor.setPosition(0.0f, 580.0f);
    floor.setFillColor(sf::Color{25, 58, 58});
    floor.setSize(sf::Vector2f{800.0f, 50.0f});

    while (window.isOpen()) {
        engine::real delta = clock.getElapsedTime().asSeconds();
        // Handle events
        sf::Event event;
        Vector acc;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    acc = Vector(-25.0f, 0.0f, 0.0f);
                    ball.move(acc);
                } else if (event.key.code == sf::Keyboard::Right) {
                    acc = Vector(25.0f, 0.0f, 0.0f);
                    ball.move(acc);
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    ball.jump();
                }
            }
        }

        // Update particle position
        ball.update(delta);

        // Clear the window
        window.clear();

        // Draw the ball
        ball.draw(window);

        // Draw the floor
        window.draw(floor);

        // Reset delta time
        clock.restart();

        // End of frame
        window.display();
    }


    return 0;
}
