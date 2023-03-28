//
// Created by dave on 27.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_PARTICLE_H
#define SIMPLE_PHYSICS_ENGINE_PARTICLE_H

#include "vector.h"

namespace engine {
    /**
    * A particle is the simplest object that can be simulated in the
    * physics system.
    */
    class Particle {

    protected:
        Vector position; /** Hold the position of the particle. */
        Vector velocity; /** Holds the velocity of the particle. */
        Vector storedForce; /** Force to be applied in next iteration. Reset at each integration */
        Vector acceleration; /** Holds the acceleration of the particle. */
        real damping; /** Holds the amount of damping applied to particle. */
        real invertedMass; /** Holds the inverted mass of the particle. */
    public:
        /**
         * Integrates the particle by updating the position and velocity.
         * This function uses the Euler integration method.
         */
        void integrate(real duration);

        /** Clears the forces applied to the particle. */
        void clearForceStorage();

        /** Return particle position */
        Vector getPosition() const;

        /** Set particle mass */
        void setMass(real mass);

        /** Set the velocity of the particle */
        void setVelocity(const Vector &velocity);

        /** Set damping value for the particle */
        void setDamping(real damping);

        /** Set the acceleration of the particle */
        void setAcceleration(const Vector &acc);


    };
}

#endif //SIMPLE_PHYSICS_ENGINE_PARTICLE_H
