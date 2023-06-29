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

namespace engine {

    /** Collision resolver responsible for resolving collisions between objects */
    class CollisionResolver {
        TEST_FRIENDS;
        private:
            struct Collision {
                GameObject* object1;
                GameObject* object2;
            };

            std::vector<Collision> collisions; /** Stores all collisions between two particles */
            real contactCoefficient = 0.75f; /** Coefficient of restitution */
            Vector contactDirection; /** Direction of contact */

        public:
            /** Add a new collision between two objects into the Collisions vector */
            void addCollision(GameObject* object1, GameObject* object2);

            /** Resolve collisions between all Particles */
            void resolve();

            /** Remove resolved collisions from the vector */
            void removeResolvedCollisions();

            /** Resolve a collision between two objects */
            void resolveCollision(GameObject* object1, GameObject*  object2);

            /** Resolve intersection between two objects */
            void resolveIntersection(GameObject* gameObject1, GameObject* gameObject2) const;

            /** Resolve collision with a wall */
            void resolveWallCollision(GameObject* collider) const;

            /** Resolve collision with a floor */
            void resolveFloorCollision(GameObject* collider) const;


    };
}

#endif //SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
