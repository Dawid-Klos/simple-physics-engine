//
// Created by dave on 14.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_SPRING_H
#define SIMPLE_PHYSICS_ENGINE_SPRING_H

#include "engine/particle.h"
#include "engine/force_generator_abstract.h"
#include "game_object.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

using namespace engine;

/**
 * Represents a spring object that can simulate spring forces.
 * Stores an instance of the Particle class to allow for applying physics.
 * */
class Spring : public GameObject {
    private:
        sf::Vertex line[2]; /** SFML object represents a line connecting anchor and spring mass */
        sf::CircleShape springMassShape; /** Stores a circle object from the SFML library to represent Spring mass */

        Particle springParticle; /** Stores an instance of Particle class for physics calculation */
        real springLength; /** Stores distance between the anchor and spring mass */

        GravityForce gravityForce; /** Interface applying gravity to the Spring object */
        SpringForce springForce; /** Interface applying spring force to the Spring object */
        DragForce dragForce = DragForce(0.0002f); /** Interface applying drag force to the Spring object */

    public:
        /** Default constructor/destructor */
        explicit Spring(real len, Vector anchorPos);
        ~Spring();

        /** Calculate forces that apply to the Spring object */
        void calculateForces();

        /** Functions to render the circle by calling SFML window */
        void draw(sf::RenderWindow &window) override;

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
