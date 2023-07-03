//
// Created by dave on 01.07.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BOX_H
#define SIMPLE_PHYSICS_ENGINE_BOX_H

#include "SFML/Graphics/RectangleShape.hpp"

#include "game_object.h"
#include <engine/force_generator_abstract.h>
#include <engine/particle.h>

using namespace engine;

/**
 * Represents a Box object (rectangle). Inherits from Game object virtual base class that requires implementation
 * of basic functions. It allows for easier manipulation of different game objects in the game world.
 *
 * It also inherits from Particle class that specifies physics properties of the Box.
 * Additionally, implements ForceGenerator interfaces to apply forces to the Box - GravityForce, DragForce
 * and FrictionForce.
 */
class Box : public virtual GameObject, public Particle {
    private:
        sf::RectangleShape shape; /**< Stores a rectangle object from the SFML library. */

        BoundingBox boundingBox{}; /**< Stores the bounding box properties. */
        void updateBoundingBox(); /**< Updates the bounding box properties of the Box. */

        real boxWidth; /**< Stores width of the box. */
        real boxHeight; /**< Stores height of the box. */

        GravityForce gravityForce = GravityForce(); /**< Interface applying gravity to the Box. */
        DragForce dragForce = DragForce(0.0009f); /**< Interface applying drag force to the Box. */
        FrictionForce frictionForce = FrictionForce(); /**< Interface applying friction force to the Box. */

    public:
        /**
         * Constructor for the Box object.
         *
         * @param width width of the box
         * @param height height of the box
         * @param posX starting x position of the box
         * @param posY starting y position of the box
         */
        Box(real width, real height, real posX, real posY);
        ~Box() override = default;

        /**
         * Draw this object by calling SFML window draw function.
         *
         * @param window SFML render window reference
         * */
        void draw(sf::RenderWindow &window) override;

        /**
         * Update this object position by calling integrate function inherited from the Particle class.
         *
         * @param delta Time step
         * */
        void update(real delta) override;

        /**
         * Returns a pointer to the Particle for accessing physics properties.
         * It is an approach used to access physics properties of the Box object.
         *
         * @return Pointer to the Particle
         * */
        Particle* getParticle() override;

        /**
        * Returns the bounding box properties.
        * It is an approach used to access bounding box properties of the Box object
        * in order to check for collisions.
        *
        * @return Bounding box properties
        * */
        [[nodiscard]] BoundingBox getBoundingBox() const override;

        /** Calculate forces that apply to the Box. */
        void calculateForces();

        /**
        * Changes the Box outline color, indicating collision
        *
        * @param color Color to be set for the outline
        * */
        void indicateCollision(sf::Color color) override;
};

#endif //SIMPLE_PHYSICS_ENGINE_BOX_H