//
// Created by dave on 17.04.23.
//
#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
#define SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H

#include <vector>
#include "particle.h"
#include "game_demo/world_objects/ball.h"

using namespace std;

namespace engine {

    /** Collision resolver responsible for resolving collisions between objects */
    class CollisionResolver {
        TEST_FRIENDS;
        private:
            struct Collision {
                GameObject* object1;
                GameObject* object2;
            };
            vector<Collision> collisions; /** Stores all collisions between two particles */
            real contactCoefficient = 0.95f; /** Coefficient of restitution */
            Vector contactDirection; /** Direction of contact */

        public:
            /** Add a collision between two objects into the vector */
            void addCollision(GameObject* object1, GameObject* object2);

            /** Resolve a collision between two objects */
            void resolveCollision(GameObject* object1, GameObject*  object2);

            /** Resolve collisions between all Particles */
            void resolve();

            /** Remove resolved collisions from the vector */
            void removeResolvedCollisions();



            /** Resolve intersection of two particles */
            static void resolveIntersection(GameObject* object1, GameObject*  object2);
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
