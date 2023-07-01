//
// Created by dave on 13.05.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H
#define SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/collision_resolver.h"
#include "engine/collision_detector.h"

using namespace engine;

class SimulationRenderer {
private:
    /** Screen dimensions */
    real WINDOW_WIDTH;
    real WINDOW_HEIGHT;

    /** SFML objects for drawing text on the screen */
    sf::Text worldInfo;
    sf::Font myFont;

    /** Stores the SFML RenderWindow object */
    sf::RenderWindow* window;
    sf::Event event{};

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

    /** Update the simulation */
    void update(const vector<GameObject*>& myObjects);

    /** Render the simulation */
    void render(const vector<GameObject*>& myObjects);

    /** Update the events */
    void updateEvents(const vector<GameObject*>& myObjects);

    /** Add objects to the collision detector system */
    void addObjectToDetector(GameObject* gameObject);

    /** Draw text on the screen */
    void drawText(const sf::String &str);
};


#endif //SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H
