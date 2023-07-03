//
// Created by dave on 24.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
#define SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/vector.h>
#include <engine/particle.h>

using namespace engine;

/**
 * Enum that represents different object types.
 * Used for collision detection purposes.
 */
enum ObjectType {
    BALL,
    SPRING,
    BOX,
    FLOOR,
    WALL
};

/**
 * Struct that represents a bounding box with minimum and maximum x and y coordinates.
 * Used for narrow collision detection phase.
 */
struct BoundingBox {
    real xMin;
    real xMax;
    real yMin;
    real yMax;
};

/**
 * Abstract base class represents a game object that can be drawn in the simulation.
 * Additionally, requires implementation of properties and methods for collision detection purposes.
 */
class GameObject {
    public:
        /** Stores the type of the object */
        ObjectType objectType{};

        virtual ~GameObject() = default;

        /** Updates the object's properties */
        virtual void update(real delta) = 0;

        /** Draws the object on the screen */
        virtual void draw(sf::RenderWindow& window) = 0;

        /** Returns a pointer to the gameObject particle */
        virtual Particle* getParticle() = 0;

        /** Returns the bounding box properties */
        [[nodiscard]] virtual BoundingBox getBoundingBox() const = 0;

        /** Indicates occurring collision by changing the outline color of an object */
        virtual void indicateCollision(sf::Color color) = 0;
};

#endif //SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
