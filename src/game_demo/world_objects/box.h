//
// Created by dave on 01.07.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_BOX_H
#define SIMPLE_PHYSICS_ENGINE_BOX_H

#include "SFML/Graphics/RectangleShape.hpp"

#include "game_object.h"
#include <engine/force_generator_abstract.h>
#include <engine/particle.h>

using namespace engine;

class Box : public virtual GameObject, public Particle {
    private:
        sf::RectangleShape shape; /** Stores a rectangle object from the SFML library */

        BoundingBox boundingBox{}; /** Stores the bounding box of a game object */
        void updateBoundingBox(); /** Update the bounding box of the Ball */

        real boxWidth; /** Stores width of the box */
        real boxHeight; /** Stores height of the wall */

        GravityForce gravityForce; /** Interface applying gravity to the Ball */
        DragForce dragForce = DragForce(0.0009f); /** Interface applying drag force to the Ball */
        FrictionForce frictionForce = FrictionForce(); /** Interface applying friction force to the Ball */

    public:
        Box();
        Box(real width, real height, real posX, real posY);

        /** Draw this object by calling SFML window */
        void draw(sf::RenderWindow &window) override;

        /** Update this object position by calling integrate function from Particle class */
        void update(real delta) override;

        /** Getter for accessing Particle instance */
        Particle* getParticle() override;

        [[nodiscard]] BoundingBox getBoundingBox() const override;

        /** Calculate forces that apply to the Ball */
        void calculateForces();

        /** Change the color of the object */
        void indicateCollision(sf::Color color) override;
};



#endif //SIMPLE_PHYSICS_ENGINE_BOX_H
