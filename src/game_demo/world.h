//
// Created by dave on 11.05.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WORLD_H
#define SIMPLE_PHYSICS_ENGINE_WORLD_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "engine/precision.h"

#include "game_demo/world_objects/spring.h"
#include "simulation_renderer.h"
#include "wall.h"

using namespace engine;

class World {
    private:
        /** Screen boundaries */
        struct ScreenBoundaries {
            GameObject* leftWall;
            GameObject* rightWall;
            GameObject* bottomWall;
            GameObject* topWall;
        };

        ScreenBoundaries screen{};

        /** Stores pointers to the Ball objects */
        std::vector<GameObject*> worldObjects;
        unsigned int ballsTimer = 0;
//
//        /** Spring object */
        Spring* spring;

        /** Stream for displaying text on the screen */
        std::ostringstream ss;

        /** Instance of SimulationRenderer used to draw objects in simulation */
        SimulationRenderer* renderer;

    public:
        explicit World(SimulationRenderer &_renderer) : renderer(&_renderer) {};

        /** Create a new Ball object */
        void createBall();

        /** Set screen boundaries - walls */
        void setScreenBoundaries(real window_width, real window_height);

        /** Crate spring system */
        void createSpringSystem(real WINDOW_WIDTH, real WINDOW_HEIGHT);

        /** Draw spring system information on the screen */
        void updateSpringSystemInfo();

        /** Update the world */
        void update();
};


#endif //SIMPLE_PHYSICS_ENGINE_WORLD_H
