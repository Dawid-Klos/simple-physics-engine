//
// Created by dave on 17.04.23.
//

#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
#define SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H

#include <engine/vector.h>
#include <vector>

#include "game_demo/world_objects/ball.h"
#include "collision_resolver.h"

using namespace std;

namespace engine {
    /**
     * Collision detector responsible for detecting objects that intersects with each other.
     */
    class CollisionDetector {
        TEST_FRIENDS;
    private:
        /** Stores pointers to all objects that occur in the simulation */
        std::vector<GameObject*> gameObjects;
        CollisionResolver& collisionResolver;

        struct Interval {
            int objectIndex;
            real min;
            real max;
        };
        std::vector<std::vector<Interval>> intervals;

    public:
        explicit CollisionDetector(CollisionResolver& resolver) : collisionResolver(resolver) {}

        /** Add a object to the collision detector */
        void addObject(GameObject* gameObject);

        /** Create intervals for each object */
        void createIntervals();

        /** Detect collisions between balls */
        void detectCollisions();
    };
}


#endif //SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
