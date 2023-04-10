//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BALL_H
#define SIMPLE_PHYSICS_ENGINE_BALL_H

#include <engine/particle.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


/** Represents a single Ball in the demo.
 * Inherits from the Particle class to allow for applying physics.
 */
class Ball : engine::Particle {
    private:
        sf::CircleShape circleShape; /** Stores a circle object from the SFML library */
        engine::real radius; /** Stored the radius of the Ball */

    public:
        /** Default contructor and destructor */
        Ball(engine::real radius);
        ~Ball();

        /** Functions to render the circle by calling SFML window */
        void update(engine::real delta, sf::Window &window);
        void draw(sf::RenderWindow &window);
        void move(engine::Vector);
        void jump();

        /** Get particle acceleration, velocity and position */
        engine::Vector getAcceleration();
        engine::Vector getVelocity();
        engine::Vector getCurrentPosition();
};

#endif //SIMPLE_PHYSICS_ENGINE_BALL_H
