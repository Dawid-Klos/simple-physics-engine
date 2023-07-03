//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BALL_H
#define SIMPLE_PHYSICS_ENGINE_BALL_H

#include <SFML/Graphics/CircleShape.hpp>

#include "engine/particle.h"
#include "engine/force_generator_abstract.h"
#include "game_object.h"

using namespace engine;

/**
 * Represents a Ball object (circle). Inherits from Game object virtual base class that requires implementation
 * of basic functions. It allows for easier manipulation of different game objects in the game world.
 *
 * It also inherits from Particle class that specifies physics properties of the Ball.
 * Additionally, implements ForceGenerator interfaces to apply forces to the Ball - GravityForce, DragForce
 * and FrictionForce.
 */
class Ball : public virtual GameObject, public Particle {
    private:
        sf::CircleShape circleShape; /**< Stores a circle object from the SFML library. */
        real radius; /**< Stores the radius of the Ball. */
        BoundingBox boundingBox{}; /**< Stores the bounding box properties. */
        void updateBoundingBox(); /**< Updates the bounding box of the Ball. */

        GravityForce gravityForce = GravityForce(); /**< Interface applying gravity to the Ball. */
        DragForce dragForce = DragForce(0.0009f); /**< Interface applying drag force to the Ball. */
        FrictionForce frictionForce = FrictionForce(); /**< Interface applying friction force to the Ball. */

    public:
        /**
         * Default constructor for the Ball object.
         *
         * @param radius Radius of the Ball
         * @param posX X position of the Ball
         * @param posY Y position of the Ball
         * */
        explicit Ball(real radius, real posX, real posY);
        ~Ball() override = default;

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
         * It is an approach used to access physics properties of the Ball object.
         *
         * @return Pointer to the Particle
         * */
        Particle* getParticle() override;

        /**
         * Changes the ball outline color, indicating collision
         *
         * @param color Color to be set for the outline
         * */
        void indicateCollision(sf::Color color) override;

        /** Calculates forces that applies to the Ball object */
        void calculateForces();

        /**
         * Returns the bounding box properties.
         * It is an approach used to access bounding box properties of the Ball object
         * in order to check for collisions.
         *
         * @return Bounding box properties
         * */
        [[nodiscard]] BoundingBox getBoundingBox() const override;

};

#endif //SIMPLE_PHYSICS_ENGINE_BALL_H
