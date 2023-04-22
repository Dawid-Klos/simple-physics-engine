#include <engine/vector.h>
#include <engine/collision_resolver.h>
#include <engine/collision_detector.h>
#include <ball.h>
#include "spring.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

using namespace engine;

const float WINDOW_WIDTH = 800.f;
const float WINDOW_HEIGHT = 600.f;

// Temp global variables
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

    // FPS limit
    unsigned int fps = 100;
    window.setFramerateLimit(fps);

    // Clock and text
    sf::Clock clock;
    engine::real delta;
    std::ostringstream ss;

    // Physics systems
    CollisionResolver collisionResolver;
    CollisionDetector detector = CollisionDetector(collisionResolver);
    vector<Ball*> myBalls;
    unsigned int ballsTimer = 0;


    Spring spring = Spring(50.0f, WINDOW_HEIGHT);

    while (window.isOpen()) {
        delta = clock.restart().asSeconds() + 0.035f;

        // Handle events
        sf::Event event;

        // World objects
        if (ballsTimer < 10) {
            Ball* ball = new Ball(850.0f * delta, 5000.0f * delta, 5500.0f * delta);
            myBalls.push_back(ball);
            detector.addBall(ball);

            ballsTimer += 1;
        }

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
        // Temp solution for screen collisions
        for (auto* ball : myBalls) {
            ball->resolveScreenCollision(WINDOW_WIDTH, WINDOW_HEIGHT);
        }

        // Print information on screen about the Spring
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
