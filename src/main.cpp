#include <engine/vector.h>
#include <engine/particle.h>

#include <SFML/Graphics.hpp>
#include <ball.h>
#include <iostream>
#include <sstream>

using namespace engine;

sf::Text myText;
sf::Font myFont;

void drawText( const sf::String &str, const int fontSize, const float posX, const float posY, sf::RenderWindow& window)
{
    myFont.loadFromFile("../Roboto-Medium.ttf");
    myText.setFont(myFont);
    myText.setString(str);
    myText.setCharacterSize(fontSize);
    myText.setPosition(posX, posY);
    window.draw(myText);
}

int main() {
    // Window
    auto const width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Physics Simulation");

    // Clock and text
    sf::Clock clock;
    std::ostringstream ss; // only output stream!

    // Objects
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
                    acc = Vector(-10.0f, 0.0f, 0.0f);
                    ball.move(acc);
                } else if (event.key.code == sf::Keyboard::Right) {
                    acc = Vector(10.0f, 0.0f, 0.0f);
                    ball.move(acc);
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::Space) {
                    ball.jump();
                }
            }
        }

        // TEST
        Vector acceleration = ball.getAcceleration();
        Vector velocity = ball.getVelocity();
        Vector position = ball.getCurrentPosition();
        ss << "Acc = x: " << acceleration.x << "  y: " << acceleration.y << std::endl;
        ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
        ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;

        // Update particle position
        ball.update(delta, window);

        // Clear the window
        window.clear();

        // Draw the ball
        ball.draw(window);

        // Draw the text
        drawText(ss.str(), 16, 10.0f, 10.0f, window);
        ss.str(std::string());

        // Draw the floor
        window.draw(floor);

        // Reset delta time
        clock.restart();

        // End of frame
        window.display();
    }

    return 0;
}
