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
                    acc = Vector(-15.0f, 0.0f, 0.0f);
                    ball.move(acc);
                } else if (event.key.code == sf::Keyboard::Right) {
                    acc = Vector(15.0f, 0.0f, 0.0f);
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

        // clear the window
        window.clear();

        // draw the ball
        ball.draw(window);

        // reset delta time
        clock.restart();

        // end
        window.display();
    }


    return 0;
}
