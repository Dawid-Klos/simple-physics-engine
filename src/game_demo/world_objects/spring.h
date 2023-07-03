//
// Created by dave on 14.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_SPRING_H
#define SIMPLE_PHYSICS_ENGINE_SPRING_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "engine/particle.h"
#include "engine/force_generator_abstract.h"
#include "game_object.h"

using namespace engine;

/**
 * Represents a Spring object. Inherits from Game object virtual base class that requires implementation
 * of basic functions. It allows for easier manipulation of different game objects in the game world.
 *
 * It also inherits from Particle class that specifies physics properties of the Spring.
 * Additionally, implements ForceGenerator interfaces to apply forces to the Spring - GravityForce, DragForce
 * and SpringForce.
 */
class Spring : public virtual GameObject, public Particle {
    private:
        sf::Vertex line[2]; /**< SFML object represents a line connecting anchor and the spring mass. */
        sf::CircleShape springMassShape; /**< Stores a circle object from the SFML library to represent Spring mass. */
        real springLength; /**< Stores the distance between the anchor and spring mass. */

        BoundingBox boundingBox{}; /**< Stores the bounding box properties. */
        void updateBoundingBox(); /**< Updates the bounding box of the Spring. */

        GravityForce gravityForce; /**< Interface applying gravity to the Spring object. */
        SpringForce springForce; /**< Interface applying spring force to the Spring object. */
        DragForce dragForce = DragForce(0.0002f); /**< Interface applying drag force to the Spring object. */

    public:
        /**
         * Default constructor for the Spring object.
         *
         * @param len Length of the spring
         * @param anchorPos Position of the anchor as a Vector with x and y coordinates
         * */
        explicit Spring(real len, Vector anchorPos);

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
        * Returns the bounding box properties.
        * It is an approach used to access bounding box properties of the Spring object
        * in order to check for collisions.
        *
        * @return Bounding box properties
        * */
        [[nodiscard]] BoundingBox getBoundingBox() const override;

        /**
        * Returns a pointer to the Particle for accessing physics properties.
        * It is an approach used to access physics properties of the Spring object.
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

        /** Calculate forces that apply to the Spring object */
        void calculateForces();
};

#endif //SIMPLE_PHYSICS_ENGINE_SPRING_H