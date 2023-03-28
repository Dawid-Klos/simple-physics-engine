#include <iostream>
#include <engine/vector.h>
#include "engine/particle.h"

#include <SFML/Graphics.hpp>



using namespace engine;

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Simulation");
    sf::Clock clock;

    sf::CircleShape particleShape(10.0f);
    particleShape.setFillColor(sf::Color::Magenta);

    sf::Vector2 position = particleShape.getPosition();
    std::cout << position.x << position.y << std::endl;
    Particle particle;
    particle.setMass(10.0f);
    particle.setDamping(0.19f);

    while (window.isOpen()) {
        // Handle events
        sf::Event event;


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    particle.setVelocity(Vector(-20.0f, 0.0f, 0.0f));
                    particle.setAcceleration(Vector(0.0f, -1.0f, 0.0f));
                } else if (event.key.code == sf::Keyboard::Right) {
                    particle.setVelocity(Vector(20.0f, 0.0f, 0.0f));
                    particle.setAcceleration(Vector(0.0f, -1.0f, 0.0f));
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Update particle position
        sf::Time delta = clock.restart();
        particle.integrate(delta.asSeconds());

        // Set SFML shape position
        particleShape.setPosition(particle.getPosition().x, particle.getPosition().y);

        // Draw SFML shape
        window.clear();
        window.draw(particleShape);
        window.display();
    }


    return 0;
}
