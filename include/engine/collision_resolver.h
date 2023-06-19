//
// Created by dave on 17.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
#define SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H

#include <vector>
#include "particle.h"
using namespace std;

namespace engine {

    /** Collision resolver responsible for resolving collisions between objects */
    class CollisionResolver {
        private:
            vector<Particle*> collidingParticles; /** Stores all colliding particles */
            real contactCoefficient = 0.85f; /** Coefficient of restitution */
            Vector contactDirection; /** Direction of contact */

        public:
            /** Add a collision between two objects into the vector */
            void addCollision(Particle *object1, Particle *object2);

            /** Resolve a collision between two objects */
            void resolveCollision(Particle* object1, Particle* object2);

            /** Resolve collisions between all Particles */
            void resolve(real delta);

            /** Remove resolved collisions from the vector */
            void removeResolvedCollisions();
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
