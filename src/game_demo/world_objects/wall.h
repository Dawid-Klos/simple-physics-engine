//
// Created by dave on 25.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_WALL_H
#define SIMPLE_PHYSICS_ENGINE_WALL_H

#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include "engine/particle.h"
#include "ball.h"
#include "game_object.h"

using namespace engine;

class Wall : public GameObject {
    private:
    sf::RectangleShape shape;
    Particle wallParticle; /** Stores an instance of Particle class for physics calculation */
    real wallWidth; /** Stores width of the wall */
    real wallHeight; /** Stores height of the wall */

    public:
    Wall();
    Wall(real width, real height, real posX, real posY, sf::Color color);

    /** Draw this object by calling SFML window */
    void draw(sf::RenderWindow &window) override;

    /** Update this object position by calling integrate function from Particle class */
    void update(real delta) override;

    /** Return the bounding box of the ball */
    BoundingBox getBoundingBox() override;

    /** Return pointer to the ball Particle */
    Particle& getParticle() override;

    /** Check if a wall collides with another object */
    bool collideWith(GameObject* other) override;
    bool collideWith(Ball* other);
    static bool collideWith(Wall* other);
};


#endif //SIMPLE_PHYSICS_ENGINE_WALL_H
