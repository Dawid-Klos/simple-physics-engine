//
// Created by dave on 17.04.23.
//

#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
#define SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H

#include <vector>

#include <engine/vector.h>
#include "collision_resolver.h"

using namespace std;

namespace engine {
    /**
     * Collision detector responsible for detecting objects that intersects with each other.
     * Sweep and prune algorithm is used to detect collisions with broad and narrow phase.
     * Broad phase is done by sorting objects along x axis and narrow phase is done by
     * checking if objects bounding boxes intersect.
     */
    class CollisionDetector {
        TEST_FRIENDS; /**< Used for testing private methods. */
    private:
        std::vector<GameObject*> gameObjects; /**< Stores pointers to all objects that occur in the simulation */

        /** Reference to the collision resolver used to call resolution of colliding objects */
        CollisionResolver& collisionResolver;

        /** Represents an interval which is used to detect collisions.
         * Each object has two intervals, one for x axis and one for y axis.
         * Each interval stores the index of the object and the min and max value of the interval.
         * */
        struct Interval {
            int objectIndex; /**< Stores the index of the object. */
            real min; /**< Stores the minimum value of the interval. */
            real max; /**< Stores the maximum value of the interval. */
        };
        std::vector<std::vector<Interval>> intervals; /**< Stores index and intervals for each object along x and y axis */

    public:
        /**
         * Collision detector constructor. Requires a reference to the collision resolver used to call
         * resolution of colliding objects.
         *
         * @param resolver Reference to the collision resolver
         * */
        explicit CollisionDetector(CollisionResolver& resolver) : collisionResolver(resolver) {}

        /**
         * Adds object to the collision detector.
         *
         * @param gameObject Pointer to the game object to be added
         * */
        void addObject(GameObject* gameObject);

        /**
         * Creates intervals for each object in the game objects vector.
         * One for x-axis and one for y-axis.
         *
         * @see Interval
         * */
        void createIntervals();

        /**
         * Uses bounding boxes to determine narrow collision detection for two objects.
         *
         * @param collider Pointer to the game object to be checked for collision
         * @param otherCollider Pointer to the other game object to be checked for collision
         *
         * @return True if the objects bounding boxes intersect, false otherwise
         * */
        static bool objectsCollides(GameObject* collider, GameObject* otherCollider);

        /**
         * Runs the algorithm to detect collisions between game objects.
         * */
        void detectCollisions();
    };
}


#endif //SIMPLE_PHYSICS_ENGINE_COLLISIONDETECTOR_H
