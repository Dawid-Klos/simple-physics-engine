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

    /**
     * Gravity force simplified to the same unit for each Particle
     * */
    class GravityForce : public ForceGeneratorAbstract {
        private:
            Vector gravity = Vector{0.0f, -25.0f, 0.0f};
        public:
            void updateForce(Vector& forceStorage) override {
                forceStorage += gravity;
            }
    };

    /**
     * DragForce applied to the Particle to simulate any fluid or air resistance
     * */
    class DragForce : public ForceGeneratorAbstract {
        private:
            real dragCoefficient = 0.0002f; /** Constant value used to calculate drag */
            Vector velocity; /** Used to store the velocity of Particle for calculations */
            Vector drag; /** Used to store the drag value that is applied to Particle after calculation */
        public:
            void getVelocityForDrag(Vector& vel) {
                velocity = vel;
            };

            void updateForce(Vector& forceStorage) override {
                real squaredSpeed = velocity.getSquaredMagnitude();
                velocity.normalize();
                velocity *= -1;
                drag.addScaledVector(velocity, dragCoefficient * squaredSpeed);

                forceStorage += drag;
            }
    };

    /**
     * Spring force calculated by the formula in Hooke's law.
     */
    class SpringForce : public ForceGeneratorAbstract {
        private:
            real k = 0.002f; /** Constant value needed to calculate spring force */
            real restLength = 0.0f; /** Length of the spring */
            Vector origin; /** Spring origin position */
            Vector otherEnd; /** Spring other end position location */

        public:
            void getSpringAttributes(Vector originPosition, Vector otherEndPosition, real length) {
                origin = originPosition;
                otherEnd = otherEndPosition;
                restLength = length;
            }
            void updateForce(Vector& forceStorage) override {
                // subtract the start and end of the spring
                Vector spring = otherEnd - origin;

                // get direction of the force by getting magnitude
                real currentLength = spring.getMagnitude();

                // normalize direction
                spring.normalize();

                // stretchLength = calc the length the spring is extended to - currentLength - restLength
                real stretchLength = currentLength - restLength;

                // finally calc
                forceStorage += spring * (-k * stretchLength);
            }
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H
