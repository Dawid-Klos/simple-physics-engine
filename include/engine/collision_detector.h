//
// Created by dave on 17.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
#define SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H

#include <engine/vector.h>
#include <vector>

#include "game_demo/ball.h"
#include "collision_resolver.h"

using namespace std;

namespace engine {
    /**
     * Collision detector responsible for detecting objects that intersects with each other.
     */
    class CollisionDetector {
    private:
        vector<Ball*> balls;
        CollisionResolver& collisionResolver;
        static bool ballsOverlap(Ball& ball1, Ball& ball2);

    public:
        explicit CollisionDetector(CollisionResolver& resolver) : collisionResolver(resolver) {}

        void addBall(Ball* ball);
        void detectCollisions();
    };
}


#endif //SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
