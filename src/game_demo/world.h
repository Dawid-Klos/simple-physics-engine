//
// Created by dave on 11.05.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WORLD_H
#define SIMPLE_PHYSICS_ENGINE_WORLD_H

#include <sstream>

#include <SFML/Graphics.hpp>

#include "world_objects/spring.h"
#include "simulation_renderer.h"

using namespace engine;

class World {
    private:
        /** Structure that represents screen boundaries */
        struct ScreenBoundaries {
            GameObject* leftWall;
            GameObject* rightWall;
            GameObject* bottomWall;
            GameObject* topWall;
        };

        ScreenBoundaries screen{};

        /** Stores pointers to all GameObjects */
        std::vector<GameObject*> worldObjects;
        unsigned int ballsTimer = 0;

        /** Spring object */
        Spring* spring{};

        /** Stream for displaying text on the screen */
        std::ostringstream ss;

        /** Instance of SimulationRenderer used to draw objects in simulation */
        SimulationRenderer* renderer;
        sf::RenderWindow* window;
        sf::Event event{};

    public:
        explicit World(SimulationRenderer &_renderer) : renderer(&_renderer) { window = renderer->getWindow(); }

        /** Update the world */
        void update();

        /** Collect user input */
        void processInput();

        /** Create a new Ball object */
        void createBall();

        /** Set screen boundaries - walls */
        void setScreenBoundaries(real window_width, real window_height);

        /** Crate spring system */
        void createSpringSystem(real WINDOW_WIDTH, real WINDOW_HEIGHT);

        /** Draw spring system information on the screen */
        void updateSpringSystemInfo();
};


#endif //SIMPLE_PHYSICS_ENGINE_WORLD_H
