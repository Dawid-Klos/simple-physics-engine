//
// Created by dave on 14.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_SPRING_H
#define SIMPLE_PHYSICS_ENGINE_SPRING_H

#include "engine/particle.h"
#include "engine/force_generator_abstract.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
using namespace engine;


/**
 * Represents a spring object that can simulate spring forces.
 * */
class Spring {
    private:
        sf::Vertex line[2];

        sf::CircleShape springMass;
        Particle springParticle;
        real springLength;
        GravityForce gravityForce;
        SpringForce springForce;
        DragForce dragForce = DragForce(0.0002f);

    public:
        /** Default constructor/destructor */
        explicit Spring(real len, real windowHeight);
        ~Spring();

        /** Calculate forces that apply to Spring */
        void calculateForces();

        /** Functions to render the circle by calling SFML window */
        void draw(sf::RenderWindow &window);

        /** Function that handles the update of position */
        void update(real delta, sf::Window &window);

        /** Moves the spring based on the acceleration applied */
        void move(Vector acc);

        /** Extends the Spring by constant value */
        void extendSpring();

        /** Get particle acceleration, velocity and position */
        Vector getCurrentAcceleration();
        Vector getCurrentVelocity();
        Vector getCurrentPosition();
};


#endif //SIMPLE_PHYSICS_ENGINE_SPRING_H
