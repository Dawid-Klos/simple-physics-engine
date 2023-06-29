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
class Spring : public virtual GameObject, public Particle {
    private:
        sf::Vertex line[2]; /** SFML object represents a line connecting anchor and spring mass */
        sf::CircleShape springMassShape; /** Stores a circle object from the SFML library to represent Spring mass */
        real springLength; /** Stores distance between the anchor and spring mass */

        BoundingBox boundingBox{}; /** Stores the bounding box of a game object */
        void updateBoundingBox(); /** Update the bounding box of the Ball */

        GravityForce gravityForce; /** Interface applying gravity to the Spring object */
        SpringForce springForce; /** Interface applying spring force to the Spring object */
        DragForce dragForce = DragForce(0.0002f); /** Interface applying drag force to the Spring object */

    public:
        /** Default constructor/destructor */
        explicit Spring(real len, Vector anchorPos);

        /** Functions to render the circle by calling SFML window */
        void draw(sf::RenderWindow &window) override;

        /** Function that handles the update of position */
        void update(real delta) override;

        /** Get spring bounding box */
        [[nodiscard]] BoundingBox getBoundingBox() const override;

        /** Return pointer to spring Particle */
        Particle* getParticle() override;

        /** Change the color of the object */
        void changeColor(sf::Color color) override;

        /** Calculate forces that apply to the Spring object */
        void calculateForces();

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
