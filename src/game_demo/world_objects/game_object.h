//
// Created by dave on 24.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
#define SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>

struct BoundingBox {
    float xMin;
    float xMax;
    float yMin;
    float yMax;
};

class GameObject {
    /**
     * Abstract base class represents a game object that can be drawn in the simulation.
     * Additionally, keep bounding box properties for collision detection purposes.
     */
public:
    virtual ~GameObject() = default;
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual engine::Particle& getParticle() = 0; /** Getter for accessing Particle instance */

    BoundingBox boundingBox{}; /** Stores the bounding box of a game object */
    virtual BoundingBox getBoundingBox() = 0;
};


#endif //SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
