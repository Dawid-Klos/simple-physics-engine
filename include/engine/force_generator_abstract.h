//
// Created by dave on 28.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H
#define SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H

#include "vector.h"
#include "particle.h"

namespace engine {
    /**
     * Force generator to be used for various kind of forces that affect a Particle.
     * Abstract class ForceGeneratorAbstract is used to create multiple classes
     * that implement specific forces using the same methods.
     * */
    class ForceGeneratorAbstract {
        virtual void updateForce(Particle *particle) = 0;
    };


    /**
     * Gravity force simplified to the same unit for each Particle.
     * Mass of a particle is not taken into account as it is applied to all forces
     * in the force storage.
     * */
    class GravityForce : public ForceGeneratorAbstract {
        private:
            Vector gravity = Vector{0.0f, -25.0f}; /**< Constant value used to calculate gravity */
        public:
            void updateForce(Particle *particle) override {
                particle->addForce(gravity);
            }
    };


    /**
     * DragForce applied to the Particle to simulate fluid or air resistance.
     * The simplified drag force formula can be expressed as: F = v^2 * A * Cd
     * Where:
     * v is the velocity of the object relative to the fluid
     * A is the cross-sectional area of the object perpendicular to the direction of motion
     * Cd is the drag coefficient, which depends on the shape of the object and the roughness of its surface
     * */
    class DragForce : public ForceGeneratorAbstract {
        private:
            real dragCoefficient; /**< Constant value used to calculate drag. */
            Vector velocity; /**< Stores the velocity of current Particle for calculations. */
        public:
            explicit DragForce(real dragConstant) : dragCoefficient(dragConstant) {};

            void updateForce(Particle *particle) override {
                velocity = particle->getVelocity();
                real speedSquared = velocity.getSquaredMagnitude();
                velocity.normalize();
                velocity *= -dragCoefficient;
                Vector drag;
                drag.addScaledVector(velocity, speedSquared);

                particle->addForce(drag);
            }
    };


    /**
     * SpringForce applied to the Particle to simulate a spring.
     * The force is calculated by the Hooke's law formula: F = -kx,
     * Where:
     * k is the spring constant,
     * and x is the displacement from the equilibrium position.
     */
    class SpringForce : public ForceGeneratorAbstract {
        private:
            real k = 0.12f; /**< Constant value needed to calculate the spring force. */
            real restLength{}; /**< Length of the spring in rest. */
            Vector origin{}; /**< Spring origin position - x and y coordinates. */

        public:
            void initSpringParameters(real restLen, Vector anchor) {
                restLength = restLen;
                origin = anchor;
            };

            void updateForce(Particle *particle) override {
                Vector currentEndPos = particle->getPosition();
                Vector springLength = currentEndPos - origin;

                real currentLength = springLength.getMagnitude();
                springLength.normalize();

                // stretchLength = the amount the spring is extended by
                real stretchLength = currentLength - restLength;

                particle->addForce(springLength * (-k * stretchLength));
            }
    };


    /**
     * A frictional force applied to a particle to simulate the resistance that arises when two surfaces
     * come into contact. The friction force is calculated by the formula: F = -u * v,
     * Where:
     * u is the friction coefficient,
     * and v is the velocity of the object relative to the surface.
     * The calculations are simplified by using constant friction coefficient.
     */
    class FrictionForce : public ForceGeneratorAbstract {
        private:
            real frictionCoefficient = 0.35f; /**< Constant value applied to the friction force formula */
        public:
            void updateForce(Particle *particle) override {
                Vector velocity = particle->getVelocity();
                velocity.normalize();
                velocity.invert();

                Vector frictionForce = velocity * frictionCoefficient;

                particle->addForce(frictionForce);
            }
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_FORCE_GENERATOR_ABSTRACT_H