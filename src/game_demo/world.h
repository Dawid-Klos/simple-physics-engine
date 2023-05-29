//
// Created by dave on 11.05.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WORLD_H
#define SIMPLE_PHYSICS_ENGINE_WORLD_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "engine/precision.h"

#include "spring.h"
#include "simulation_renderer.h"

using namespace engine;

class World {
    private:
    /** Stores pointers to the Ball objects */
    vector<Ball*> myBalls;
    unsigned int ballsTimer = 0;

    /** Spring object */
    Spring spring = Spring(0.0f, 0.0f);

    /** Stream for displaying text on the screen */
    std::ostringstream ss;

    /** Instance of SimulationRenderer used to draw to window */
    SimulationRenderer* renderer;

    public:
        explicit World(SimulationRenderer &_renderer) : renderer(&_renderer) {};

        /** Create balls */
        void createBalls();

        /** Crate spring system */
        void createSpringSystem(real WINDOW_HEIGHT);

        /** Draw spring system information on the screen */
        void updateSpringSystemInfo();

        /** Update the world */
        void update();

};


#endif //SIMPLE_PHYSICS_ENGINE_WORLD_H
