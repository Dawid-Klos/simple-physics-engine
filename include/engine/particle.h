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
    private:
        Vector position; /** Hold the position of the particle. */
        Vector velocity; /** Holds the velocity of the particle. */
        Vector acceleration; /** Holds the acceleration of the particle. */
        real invertedMass; /** Holds the inverted mass of the particle. */
        real damping; /** Holds the amount of damping applied to particle. */
        Vector forceStorage; /** Holds the accumulated forces */

    public:
        /** Return position of given Particle */
        [[nodiscard]] Vector getPosition() const;
        void getPosition(Vector *pos) const;

        /** Set position for given Particle */
        void setPosition(real x, real y);

        /** Set velocity for given Particle */
        void setVelocity(const Vector &velocity);
        void setVelocity(real x, real y);

        /** Get velocity for given Particle */
        [[nodiscard]] Vector getVelocity() const;

        /** Set acceleration for given Particle */
        void setAcceleration(const Vector &acc);
        void setAcceleration(real x, real y);

        /** Get acceleration for given Particle */
        [[nodiscard]] Vector getAcceleration() const;

        /** Set the damping value for given Particle */
        void setDamping(real value);

        /** Get mass for given Particle */
        [[nodiscard]] real getMass() const;

        /** Set mass for given Particle. The value is stored as 1/mass */
        void setMass(real mass);

        /** Perform integration by using the Euler method */
        void integrate(real delta);

        /** Add force to the force storage */
        void addForce(Vector force);

        /** Clear the storage from accumulated forces */
        void clearForceStorage();
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_PARTICLE_H
