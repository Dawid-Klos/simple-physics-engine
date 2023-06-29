//
// Created by dave on 24.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
#define SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/vector.h>
class Wall;
class Ball;

using namespace engine;

enum ObjectType {
    BALL,
    SPRING,
    FLOOR,
    WALL
};

struct BoundingBox {
    float xMin;
    float xMax;
    float yMin;
    float yMax;
};

class GameObject {
    /**
     * Abstract base class represents a game object that can be drawn in the simulation.
     * Additionally, requires implementation of properties and methods for collision detection purposes.
     */
public:
    ObjectType objectType{};

    virtual ~GameObject() = default;
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual Particle* getParticle() = 0; /** Getter for accessing Particle instance */
    [[nodiscard]] virtual BoundingBox getBoundingBox() const = 0; /** Getter for accessing the bounding box properties */
    virtual void changeColor(sf::Color color) = 0; /** Change the color of the object */
};

#endif //SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
