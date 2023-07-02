//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BALL_H
#define SIMPLE_PHYSICS_ENGINE_BALL_H

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/particle.h"
#include "engine/force_generator_abstract.h"
#include "game_object.h"
#include "wall.h"

using namespace engine;

/**
 * Represents a single Ball shape object. Inherits from Game object base class.
 * Stores an instance of the Particle class to allow for applying physics.
 */
class Ball : public virtual GameObject, public Particle {
    private:
        sf::CircleShape circleShape; /** Stores a circle object from the SFML library */
        real radius; /** Stores the radius of the Ball */
        BoundingBox boundingBox{}; /** Stores the bounding box of a game object */
        void updateBoundingBox(); /** Update the bounding box of the Ball */

        GravityForce gravityForce; /** Interface applying gravity to the Ball */
        DragForce dragForce = DragForce(0.0009f); /** Interface applying drag force to the Ball */
        FrictionForce frictionForce = FrictionForce(); /** Interface applying friction force to the Ball */

    public:
        /** Default constructor and destructor */
        explicit Ball(real radius, real posX, real posY);
        ~Ball() override = default;

        /** Draw this object by calling SFML window */
        void draw(sf::RenderWindow &window) override;

        /** Update this object position by calling integrate function from Particle class */
        void update(real delta) override;

        /** Getter for accessing Particle instance */
        Particle* getParticle() override;

        /** Change the ball color */
        void indicateCollision(sf::Color color) override;

        /** Calculate forces that apply to the Ball */
        void calculateForces();

        /** Getter for accessing the bounding box properties */
        [[nodiscard]] BoundingBox getBoundingBox() const override;

};

#endif //SIMPLE_PHYSICS_ENGINE_BALL_H
