#include <engine/vector.h>
#include <ball.h>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "spring.h"

using namespace engine;

sf::Text myText;
sf::Font myFont;

void drawText(const sf::String &str, const int fontSize, const float posX, const float posY, sf::RenderWindow& window)
{
    myFont.loadFromFile("../Roboto-Medium.ttf");
    myText.setFont(myFont);
    myText.setFillColor(sf::Color(48,54,47));
    myText.setString(str);
    myText.setCharacterSize(fontSize);
    myText.setPosition(posX, posY);
    window.draw(myText);
}

int main() {
    // enable anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    auto const width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Physics Simulation", sf::Style::Default, settings);

    unsigned int fps = 100;
    window.setFramerateLimit(fps);

    // Clock and text
    sf::Clock clock;
    engine::real delta;
    engine::real lastTime = 0.0f;
    std::ostringstream ss;

    // Objects
//    Ball lightBall = Ball(25.0f);
//    Ball heavyBall = Ball(50.0f);
    Spring spring = Spring(100.0f);

    while (window.isOpen()) {
        // hacky solution to slow rendering
        delta = clock.restart().asSeconds() + 0.035f;
        // delta = clock.restart().asSeconds();

        // Handle events
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left) {
//                        lightBall.move(Vector(-15.0f, 0.0f, 0.0f));
                        spring.move(Vector(-45.0f, 0.0f, 0.0f));
                    } else if (event.key.code == sf::Keyboard::Right) {
//                        lightBall.move(Vector(15.0f, 0.0f, 0.0f));
                        spring.move(Vector(45.0f, 0.0f, 0.0f));
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    } else if (event.key.code == sf::Keyboard::Space) {
//                        lightBall.jump();
                        spring.extendSpring();
                    }
                    break;
                default:
                    break;
            }
        }

//        Vector acceleration = lightBall.getCurrentAcceleration();
//        Vector velocity = lightBall.getCurrentVelocity();
//        Vector position = lightBall.getCurrentPosition();
        Vector acceleration = spring.getCurrentAcceleration();
        Vector velocity = spring.getCurrentVelocity();
        Vector position = spring.getCurrentPosition();
        ss << "Acc = x: " << acceleration.x << "  y: " << acceleration.y << std::endl;
        ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
        ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;

        // Update particle position
//        lightBall.update(delta, window);
//        heavyBall.update(delta, window);
        spring.update(delta, window);

        // Clear the window
        window.clear(sf::Color(255, 251, 219));

        // Draw the ball
//        lightBall.draw(window);
//        heavyBall.draw(window);
        spring.draw(window);

        // Draw the text
        drawText(ss.str(), 16, 10.0f, 10.0f, window);
        ss.str(std::string());

        // End of frame
        window.display();
    }
    return 0;
}
