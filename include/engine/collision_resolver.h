//
// Created by dave on 17.04.23.
//
#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
#define SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H

#include <vector>
#include "game_demo/world_objects/game_object.h"

namespace engine {

    /**
     * Collision resolver responsible for resolving collisions between objects.
     * Collision detector is responsible for detecting collisions between objects and passing them over
     * to the Collision resolver. Then appropriate resolution is chosen and applied to the objects.
     * Lastly, the collision is removed from the vector.
     * */
    class CollisionResolver {
        TEST_FRIENDS; /**< Used for testing to access private properties. */
        private:
            /**
             * Struct that represents a collision between two objects.
             *
             * @see addCollision
             * */
            struct Collision {
                GameObject* object1;
                GameObject* object2;
            };

            std::vector<Collision> collisions; /**< Stores all collisions between the game objects for current frame. */
            real contactCoefficient = 0.85f; /**< Coefficient of restitution. */
            Vector contactDirection; /**< Direction of contact. */

        public:
            /**
             * Add a new collision between two objects into the Collisions vector.
             *
             * @param object1 Pointer to the first colliding object
             * @param object2 Pointer to the second colliding object
             * */
            void addCollision(GameObject* object1, GameObject* object2);

            /**
             * Resolve collisions between all Particles and clears the vector after.
             * Also, decides which type of resolution should be applied to the collision.
             *
             * @see resolveCollision
             * */
            void resolve();

            /**
             * Remove resolved collisions from the vector.
             * */
            void removeResolvedCollisions();

            /**
             * Resolve a collision between two dynamic objects.
             *
             * @param object1 Pointer to the first colliding object
             * @param object2 Pointer to the second colliding object
             * */
            void resolveCollision(GameObject* object1, GameObject*  object2);

            /**
             * Resolve collision of a dynamic object with static wall.
             *
             * @param collider Pointer to the colliding object
             * */
            void resolveWallCollision(GameObject* collider) const;

            /**
             * Resolve collision with a floor (ground).
             *
             * @param collider Pointer to the colliding object
             * */
            void resolveFloorCollision(GameObject* collider) const;

            /**
             * Return the current number of occurring collisions stored in the vector.
             *
             * @return Number of collisions
             * */
            [[nodiscard]] unsigned int getCollisionsSize() const;
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H