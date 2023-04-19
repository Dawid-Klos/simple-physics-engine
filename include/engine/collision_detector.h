//
// Created by dave on 17.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
#define SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H

#include <engine/vector.h>
#include <vector>
#include "ball.h"
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
        unsigned int collisions = 0;
    public:
        explicit CollisionDetector(CollisionResolver& resolver) : collisionResolver(resolver) {}

        void addBall(Ball* ball);
        void detectCollisions();
        void checkForCollision(Ball& ball, Ball& ball2);
    };
}


#endif //SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
