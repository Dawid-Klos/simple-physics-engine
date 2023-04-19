//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BALL_H
#define SIMPLE_PHYSICS_ENGINE_BALL_H

#include <engine/particle.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "engine/force_generator_abstract.h"

using namespace engine;

/**
 * Represents a single Ball shape object.
 * Inherits from the Particle class to allow for applying physics.
 */
class Ball {
    private:
        sf::CircleShape circleShape; /** Stores a circle object from the SFML library */
        real radius; /** Stores the radius of the Ball */
        Particle ballParticle; /** Stored the Particle object for physics calculation */
        GravityForce gravityForce; /** Used for adding gravity to the Ball */
        DragForce dragForce = DragForce(0.001f); /** Used for adding drag force to the Ball */

    public:
        /** Default constructor and destructor */
        explicit Ball(real radius, real posX, real posY);
        ~Ball();

        /** Functions to render the circle by calling SFML window */
        void draw(sf::RenderWindow &window);

        /** Function that handles the update of position */
        void update(real delta, sf::Window &window);

        /** Calculate forces that apply to the Ball */
        void calculateForces();

        /** Return pointer to the ball Particle */
        Particle* getParticle();

        /** Get particle radius */
        real getRadius() const;

        /** Functions called to move the ball */
        void move(Vector);
        void jump();

        /** Change the ball color */
        void changeColor(sf::Color color);

        /** Get particle acceleration, velocity and position */
        Vector getCurrentAcceleration();
        Vector getCurrentVelocity();
        Vector getCurrentPosition();

        void resolveScreenCollision(float WINDOW_WIDTH, float WINDOW_HEIGHT);
};

#endif //SIMPLE_PHYSICS_ENGINE_BALL_H
