//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H
#define SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H

#include "vector.h"
#include "particle.h"

namespace engine {
    /**
     * Force generator to be used for various kind of forces that affect the Particle.
     * Abstract class ForceGeneratorAbstract is used to create multiple classes
     * that implement specific forces using the same methods.
     * */
    class ForceGeneratorAbstract {
        virtual void updateForce(Particle *particle) = 0;
    };

    /**
     * Gravity force simplified to the same unit for each Particle
     * */
    class GravityForce : public ForceGeneratorAbstract {
        private:
            Vector gravity = Vector{0.0f, -25.0f, 0.0f};
        public:
            void updateForce(Particle *particle) override {
                particle->addForce(gravity);
            }
    };

    /**
     * DragForce applied to the Particle to simulate fluid or air resistance.
     * */
    class DragForce : public ForceGeneratorAbstract {
        private:
            real dragCoefficient = 0.0002f; /** Constant value used to calculate drag */
            Vector velocity; /** Used to store the velocity of Particle for calculations */
            Vector drag; /** Used to store the drag value that is applied to Particle after calculation */
        public:
            void updateForce(Particle *particle) override {
                velocity = particle->getVelocity();
                real squaredSpeed = velocity.getSquaredMagnitude();
                velocity.normalize();
                velocity *= -1;
                drag.addScaledVector(velocity, dragCoefficient * squaredSpeed);

                particle->addForce(drag);
            }
    };

    /**
     * Spring force calculated by the formula in Hooke's law.
     */
    class SpringForce : public ForceGeneratorAbstract {
        private:
            real k = 0.1f; /** Constant value needed to calculate spring force */
            real restLength; /** Length of the spring */
            Vector origin; /** Spring origin position */
            Vector otherEnd; /** Spring other end position location */

        public:
            void updateForce(Particle *particle) override {
                restLength = particle->getSpringRestLength();
                otherEnd = particle->getPosition();
                origin = particle->getSpringOriginPosition();

                // subtract the start and end of the spring
                Vector spring = otherEnd - origin;

                // get direction of the force by getting magnitude
                real currentLength = spring.getMagnitude();

                // normalize direction
                spring.normalize();

                // stretchLength = calc the length the spring is extended to - currentLength - restLength
                real stretchLength = currentLength - restLength;

                // finally calc
                particle->addForce(spring * (-k * stretchLength));
            }
    };

    /**
     * A frictional force applied to a particle to simulate the resistance
     * that arises when two surfaces come into contact.
     */
    class FrictionForce : public ForceGeneratorAbstract {
        private:
            real frictionCoefficient = 0.01f; /** Constant value applied to the friction force formula */
            Vector velocity;  /** Used to store the velocity of Particle for calculations */
            Vector frictionForce; /** Used to store the friction force that is applied to Particle */
        public:
            void updateForce(Particle *particle) override {
                velocity = particle->getVelocity();
                velocity.normalize();
                frictionForce.addScaledVector(velocity, -1);
                frictionForce *= frictionCoefficient;

                particle->addForce(frictionForce);
            }
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H
