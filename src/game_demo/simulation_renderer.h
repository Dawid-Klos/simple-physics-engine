//
// Created by dave on 13.05.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H
#define SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/precision.h"
#include "engine/collision_resolver.h"
#include "engine/collision_detector.h"
#include "spring.h"

using namespace engine;

class SimulationRenderer {
private:
    /** Screen dimensions */
    real WINDOW_WIDTH = 800.0f;
    real WINDOW_HEIGHT = 600.0f;

    /** SFML objects for drawing text on the screen */
    sf::Text myText;
    sf::Font myFont;

    /** Stores the SFML RenderWindow object */
    sf::RenderWindow* window;
    sf::Event event;

    /** SFML object used to measure time between frames */
    sf::Clock clock;
    real delta = 0.0f;

    /** Collision detection system */
    CollisionResolver collisionResolver;
    CollisionDetector collisionDetector = CollisionDetector(collisionResolver);

public:
    /** Default constructor */
    SimulationRenderer(real width, real height);
    virtual ~SimulationRenderer();

    /** Check if the window is open and return a boolean */
    bool running() const;

    /** Add objects to the collision detector system */
    void addObjectToDetector(Ball* ball);

    /** Update the events */
    void updateEvents(vector<Ball*>& balls, Spring &spring);

    /** Update the simulation */
    void update(const vector<Ball*>& balls, Spring &spring);

    /** Render the simulation */
    void render(const vector<Ball*>& myBalls, Spring& spring);

    /** Draw text on the screen */
    void drawText(const sf::String &str);

    /** Return delta */
    real getDelta() const;

    /** Return a pointer to the window */
    sf::RenderWindow *getWindow() const;
};


#endif //SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H
