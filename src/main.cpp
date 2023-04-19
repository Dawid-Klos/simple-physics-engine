#include <engine/vector.h>
#include <ball.h>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "spring.h"
#include "engine/collision_resolver.h"
#include "engine/collision_detector.h"

using namespace engine;

const float WINDOW_WIDTH = 800.f;
const float WINDOW_HEIGHT = 600.f;

sf::Text myText;
sf::Font myFont;

void drawText(const sf::String &str, const int fontSize, const float posX, const float posY, sf::RenderWindow& window)
{
    myFont.loadFromFile("../assets/Roboto-Medium.ttf");
    myText.setFont(myFont);
    myText.setFillColor(sf::Color(48,54,47));
    myText.setString(str);
    myText.setCharacterSize(fontSize);
    myText.setPosition(posX, posY);
    myText.setScale(1.0, -1.0);

    window.draw(myText);
}

int main() {
    // enable anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window
    sf::RenderWindow window(sf::VideoMode((unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT), "Physics Simulation", sf::Style::Default, settings);
    sf::View view = window.getDefaultView();
    view.setSize(WINDOW_WIDTH, -WINDOW_HEIGHT);
    window.setView(view);

    // fps limit
    unsigned int fps = 80;
    window.setFramerateLimit(fps);

    // Clock and text
    sf::Clock clock;
    engine::real delta;
    std::ostringstream ss;

    // Physics systems
    CollisionResolver collisionResolver;
    CollisionDetector detector = CollisionDetector(collisionResolver);
    vector<Ball*> myBalls;

    // World objects
    for (unsigned int i = 1; i < 20; i++) {
        Ball* ball = new Ball(10.0f + real(i), real(5.0 * i), real(100.0 / i));
        myBalls.push_back(ball);
        detector.addBall(ball);
    }

    Spring spring = Spring(100.0f);

    while (window.isOpen()) {
        delta = clock.restart().asSeconds() + 0.035f;

        // Handle events
        sf::Event event;

        for (auto* ball : myBalls) {
            ball->changeColor(sf::Color{169, 151, 223});
        }

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left) {
//                        lightBall->move(Vector(-15.0f, 0.0f, 0.0f));
                        spring.move(Vector(-45.0f, 0.0f, 0.0f));
                    } else if (event.key.code == sf::Keyboard::Right) {
//                        lightBall->move(Vector(15.0f, 0.0f, 0.0f));
                        spring.move(Vector(45.0f, 0.0f, 0.0f));
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    } else if (event.key.code == sf::Keyboard::Space) {
//                        lightBall->jump();
                        spring.extendSpring();
                    }
                    break;
                default:
                    break;
            }
        }
        for (auto* ball : myBalls) {
            ball->resolveScreenCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
        }

        Vector acceleration = spring.getCurrentAcceleration();
        Vector velocity =  spring.getCurrentVelocity();
        Vector position =  spring.getCurrentPosition();
        ss << "Acc = x: " << acceleration.x << "  y: " << acceleration.y << std::endl;
        ss << "Vel = x: " << velocity.x << "  y: " << velocity.y << std::endl;
        ss << "Pos = x: " << position.x << "  y: " << position.y << std::endl;
        ss << "MousePos = x: " << sf::Mouse::getPosition(window).x << "  y: " << sf::Mouse::getPosition(window).y << std::endl;

        // Collision detection
        detector.detectCollisions();
        collisionResolver.resolve(delta);
        collisionResolver.removeResolvedCollisions();

        // Update particle position
        for (auto* ball : myBalls) {
            ball->update(delta, window);
        }
        spring.update(delta, window);

        // Clear the window
        window.clear(sf::Color(255, 251, 219));

        // Draw the objects
        for (auto* ball : myBalls) {
            ball->draw(window);
        }

        spring.draw(window);

        // Draw the text
        drawText(ss.str(), 24, 10.0f, WINDOW_HEIGHT - 10.0f , window);
        ss.str(std::string());

        // End of frame
        window.display();
    }
    return 0;
}
