//
// Created by dave on 14.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_SPRING_H
#define SIMPLE_PHYSICS_ENGINE_SPRING_H

#include "engine/particle.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

/** Represents a line object */
class Spring : engine::Particle {
    private:
        sf::Vertex line[2];
        sf::CircleShape springMass;
        engine::real restLength;
        engine::SpringForce springForce;

    public:
        /** Default constructor/destructor */
        explicit Spring(engine::real springLength);
        ~Spring();

        /** Create needed forces for current object */
        void initSpringForce();

        /** Functions to render the circle by calling SFML window */
        void draw(sf::RenderWindow &window);

        /** Function that handles the update of position */
        void update(engine::real delta, sf::Window &window);

        void move(engine::Vector acc);

        void extendSpring();

        /** Get particle acceleration, velocity and position */
        engine::Vector getCurrentAcceleration();
        engine::Vector getCurrentVelocity();
        engine::Vector getCurrentPosition();
};


#endif //SIMPLE_PHYSICS_ENGINE_SPRING_H
