//
// Created by dave on 25.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WALL_H
#define SIMPLE_PHYSICS_ENGINE_WALL_H

#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/particle.h"
#include "game_object.h"
#include "ball.h"

using namespace engine;

/**
 * Represents a Wall object (rectangle). Inherits from Game object virtual base class that requires implementation
 * of basic functions. It allows for easier manipulation of different game objects in the game world.
 *
 * It also inherits from Particle class that specifies physics properties of the Wall. Is is a static
 * object, so there is no implementation of integrate function and the mass is set to 0.
 *
 */
class Wall : public virtual GameObject, public Particle {
    private:
        sf::RectangleShape shape; /**< Stores a rectangle object from the SFML library. */
        BoundingBox boundingBox{}; /**< Stores the bounding box properties. */

        real wallWidth; /**< Stores width of the wall. */
        real wallHeight; /**< Stores height of the wall. */

    public:
        /**
         * Default constructor for the Wall object.
         *
         * @param width width of the wall
         * @param height height of the wall
         * @param posX starting x position of the wall
         * @param posY starting y position of the wall
         */
        Wall(real width, real height, real posX, real posY);

        /**
         * Draws this object by calling the SFML render window draw function.
         *
         * @param window SFML render window reference
         * */
        void draw(sf::RenderWindow &window) override;

        /**
         * Updates position by calling integrating function inherited from the Particle class.
         *
         * @param delta Time step
         * */
        void update(real delta) override;

        /**
        * Returns a pointer to the Particle for accessing physics properties.
        * It is an approach used to access physics properties of the Wall object.
        *
        * @return Pointer to the Particle
        * */
        Particle* getParticle() override;

        /**
        * Returns the bounding box properties.
        * It is an approach used to access bounding box properties of the Ball object
        * in order to check for collisions.
        *
        * @return Bounding box properties
        * */
        [[nodiscard]] BoundingBox getBoundingBox() const override;

        /**
        * Changes the ball outline color, indicating collision
        *
        * @param color Color to be set for the outline
        * */
        void indicateCollision(sf::Color color) override;
};


#endif //SIMPLE_PHYSICS_ENGINE_WALL_H
