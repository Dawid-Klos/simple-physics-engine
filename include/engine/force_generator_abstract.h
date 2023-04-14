//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H
#define SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H

#include "vector.h"

namespace engine {
    /**
     * Force generator to be used for various kind of forces that affect the Particle.
     * Abstract class ForceGeneratorAbstract is used to create multiple classes
     * that implement specific forces using the same methods.
     * */
    class ForceGeneratorAbstract {
        virtual void updateForce(Vector& forceStorage) = 0;
    };

    class GravityForce : public ForceGeneratorAbstract {
        private:
            Vector gravity = Vector{0.0f, -100.0f, 0.0f};
        public:
            void updateForce(Vector& forceStorage) override {
                forceStorage += gravity;
            }
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H
