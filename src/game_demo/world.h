//
// Created by dave on 11.05.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WORLD_H
#define SIMPLE_PHYSICS_ENGINE_WORLD_H

#include <sstream>
#include <SFML/Graphics.hpp>

#include "simulation_renderer.h"

using namespace engine;
/**
 * Class that represents the world of the simulation. It is responsible for setting the screen boundaries,
 * creating new objects, processing user input and updating the simulation.
 *
 * @see SimulationRenderer
 */
class World {
    private:
        /** Structure that represents screen boundaries.
         *
         * @see setScreenBoundaries
         * */
        struct ScreenBoundaries {
            GameObject* leftWall;
            GameObject* rightWall;
            GameObject* bottomWall;
            GameObject* topWall;
        };

        ScreenBoundaries screen{}; /**< Stores an object containing pointers to the screen boundaries. */
        std::vector<GameObject*> worldObjects; /**< Stores pointers to all GameObjects that occurs in the simulation */

        unsigned int ballsTimer = 0; /**< Timer used to create new balls in the simulation. */

        std::ostringstream ss; /**< Stream for displaying text on the screen. */
        SimulationRenderer* renderer; /**< A pointer to the instance of SimulationRenderer used to render and draw objects in simulation. */
        sf::RenderWindow* window; /**< Stores a pointer to the RenderWindow object. */
        sf::Event event{}; /**< SFML event object used to process user input. */

    public:
        explicit World(SimulationRenderer &_renderer) : renderer(&_renderer) { window = renderer->getWindow(); }

        /**
         * Updates the state of the world by updating all objects in the simulation.
         * It processes input, updates objects and then renders them by calling the renderer.
         * */
        void update();

        /**
         * Collects the user input and performs specified
         * */
        void processInput();

        /**
         * Creates a new Ball object and adds it into the simulation.
         * Balls counter is used to create a defined number of balls in the simulation.
         * */
        void createBall();

        /**
         * Sets the screen boundaries - walls, floor and ceiling.
         *
         * @param window_width width of the window.
         * @param window_height height of the window.
         * */
        void setScreenBoundaries(real window_width, real window_height);

        /**
         * Crates spring system and places it in the middle of the screen based on the window size.
         *
         * @param WINDOW_WIDTH width of the window.
         * @param WINDOW_HEIGHT height of the window.
         * */
        void createSpringSystem(real WINDOW_WIDTH, real WINDOW_HEIGHT);

        /** Draws spring system information on the screen */
        void updateSpringSystemInfo();
};

#endif //SIMPLE_PHYSICS_ENGINE_WORLD_H