//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BALL_H
#define SIMPLE_PHYSICS_ENGINE_BALL_H

#include "engine/particle.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "engine/force_generator_abstract.h"
#include "game_object.h"

using namespace engine;

/**
 * Represents a single Ball shape object. Inherits from Game object base class.
 * Stores an instance of the Particle class to allow for applying physics.
 */
class Ball : public virtual GameObject {
    private:
        sf::CircleShape circleShape; /** Stores a circle object from the SFML library */
        real radius; /** Stores the radius of the Ball */
        Particle ballParticle; /** Stores an instance of Particle class for physics calculation */
        GravityForce gravityForce; /** Interface applying gravity to the Ball */
        DragForce dragForce = DragForce(0.0009f); /** Interface applying drag force to the Ball */

        void updateBoundingBox(); /** Update the bounding box of the Ball */

    public:
        /** Default constructor and destructor */
        explicit Ball(real radius, real posX, real posY);

        /** Draw this object by calling SFML window */
        void draw(sf::RenderWindow &window) override;

        /** Update this object position by calling integrate function from Particle class */
        void update(real delta) override;

        /** Calculate forces that apply to the Ball */
        void calculateForces();

        /** Return the bounding box of the ball */
        BoundingBox getBoundingBox() override;

        /** Return pointer to the ball Particle */
        Particle& getParticle() override;

        /** Get particle radius */
        real getRadius() const;

        /** Functions called to move the ball */
        void move(Vector);

        /** Change the ball color */
        void changeColor(sf::Color color);

        void resolveScreenCollision(float WINDOW_WIDTH, float WINDOW_HEIGHT);
};

#endif //SIMPLE_PHYSICS_ENGINE_BALL_H
