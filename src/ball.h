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
        engine::Particle circleParticle;
        sf::CircleShape circleShape; /** Stores a circle object from the SFML library */
        engine::real radius; /** Stored the radius of the Ball */
        bool isPressed; /** If true the ball being dragged, false otherwise */

    public:
        Ball(engine::real radius);
        ~Ball();

        /** Set the ball to isPressed and not */
        void setPressed(bool isPressed);

        /** Functions to render the circle by calling SFML window */
        void update(engine::real delta);
        void draw(sf::RenderWindow& window);
        void move(engine::Vector);
        void jump();
};

#endif //SIMPLE_PHYSICS_ENGINE_BALL_H
