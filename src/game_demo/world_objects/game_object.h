//
// Created by dave on 24.06.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
#define SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
public:
    virtual void update(float delta) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};


#endif //SIMPLE_PHYSICS_ENGINE_GAME_OBJECT_H
