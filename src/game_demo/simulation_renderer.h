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
    /**
     * SimulationRenderer is responsible for rendering the simulation. It uses SFML library to draw objects
     * on the screen. It also stores the CollisionDetector and CollisionResolver classes to detect and resolve
     * collisions between objects.
     */
    class SimulationRenderer {
        private:
            /** Stores screen dimensions */
            real WINDOW_WIDTH;
            real WINDOW_HEIGHT;

            /** SFML objects for drawing text on the screen */
            sf::Text worldInfo;
            sf::Font myFont;

            /** Stores a pointer to SFML RenderWindow object */
            sf::RenderWindow* window;

            /** SFML object used to measure time between frames */
            sf::Clock clock;
            real delta = 0.0f;

            /** Collision detection system */
            CollisionResolver collisionResolver;
            CollisionDetector collisionDetector = CollisionDetector(collisionResolver);
            unsigned int collisionsCount = 0;

        public:
            /** Default constructor */
            SimulationRenderer(real width, real height);
            virtual ~SimulationRenderer();

            /**
             * Returns a boolean value indicating if the simulation is running.
             *
             * @return true if the simulation is running, false otherwise
             * */
            bool running() const;

            /**
             * Updates all objects in the simulation provided as a vector of pointers to GameObjects.
             *
             * @param myObjects vector of pointers to GameObjects
             * */
            void update(const vector<GameObject*>& myObjects);

            /**
             * Renders all objects in the simulation provided as a vector of pointers to GameObjects.
             *
             * @param myObjects vector of pointers to GameObjects
             * */
            void render(const vector<GameObject*>& myObjects);

            /**
             * Returns a pointer to the SFML RenderWindow object.
             *
             * @return pointer to the SFML RenderWindow object
             * */
            sf::RenderWindow* getWindow() const;

            /**
             * Returns current number of objects in the collision detector system.
             * Used for displaying information about the simulation.
             *
             * @return current number of objects in the collision detector system
             * */
            unsigned int getCollisionsCount() const;

            /**
             * Adds object to the collision detector system.
             *
             * @param gameObject pointer to the GameObject to be added to the collision detector system
             * */
            void addObjectToDetector(GameObject* gameObject);

            /**
             * Draws text on the screen.
             * Used for displaying information about the simulation.
             *
             * @param str string to be drawn on the screen
             * */
            void drawText(const sf::String &str);
    };

#endif //SIMPLE_PHYSICS_ENGINE_SIMULATION_RENDERER_H