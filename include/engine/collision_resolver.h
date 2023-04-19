//
// Created by dave on 17.04.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
#define SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H

#include <vector>
#include "particle.h"
using namespace std;
namespace engine {

    class CollisionResolver {
        private:
            vector<Particle*> collidingParticles;
            real contactCoefficient = 0.8f;
            Vector contactDirection;

        public:
            void addCollision(Particle *object1, Particle *object2);
            void resolve(real delta);
            void removeResolvedCollisions();
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_COLLISION_RESOLVER_H
