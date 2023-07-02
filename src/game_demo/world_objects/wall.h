//
// Created by dave on 25.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WALL_H
#define SIMPLE_PHYSICS_ENGINE_WALL_H

#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/particle.h"
#include "game_object.h"
#include "ball.h"

using namespace engine;

class Wall : public virtual GameObject, public Particle {
    private:
        sf::RectangleShape shape; /** Stores a rectangle object from the SFML library */
        BoundingBox boundingBox{}; /** Stores the bounding box of a game object */

        real wallWidth; /** Stores width of the wall */
        real wallHeight; /** Stores height of the wall */

    public:
        Wall();
        Wall(real width, real height, real posX, real posY);

        /** Draw this object by calling SFML window */
        void draw(sf::RenderWindow &window) override;

        /** Update this object position by calling integrate function from Particle class */
        void update(real delta) override;

        /** Getter for accessing Particle instance */
        Particle* getParticle() override;

        [[nodiscard]] BoundingBox getBoundingBox() const override;

        /** Change the color of the object */
        void indicateCollision(sf::Color color) override;
};


#endif //SIMPLE_PHYSICS_ENGINE_WALL_H
