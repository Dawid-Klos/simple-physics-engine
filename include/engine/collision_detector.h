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

        struct Interval {
            int objectIndex;
            float min;
            float max;
        };

        std::vector<std::vector<Interval>> intervals;

    public:
        explicit CollisionDetector(CollisionResolver& resolver) : collisionResolver(resolver) {}

        /** Add a ball object to the collision detector */
        void addBall(Ball* ball);

        /** Create intervals for each ball */
        void createIntervals();

        /** Update bounding boxes of all balls */
        void updateBoundingBoxes();

        /** Detect collisions between balls */
        void detectCollisions();
    };
}


#endif //SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
