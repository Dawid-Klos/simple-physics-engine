//
// Created by dave on 27.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_PARTICLE_H
#define SIMPLE_PHYSICS_ENGINE_PARTICLE_H

#include "vector.h"

namespace engine {

    /**
    * Represents a particle which is the simplest object that can be simulated in the physics system.
    * It has position data (without orientation), along with velocity, acceleration, mass and damping value.
    * It can be integrated forward through time, and have linear forces, and impulses applied to it.
    */
    class Particle {
        private:
            Vector position; /**< Stores the position of a particle. */
            Vector velocity; /**< Stores the velocity of a particle. */
            Vector acceleration; /**< Stores the acceleration of a particle. */
            real invertedMass{}; /**< Stores the inverted mass of a particle. */
            real damping{}; /**< Stores the amount of damping applied each frame to a particle. */
            Vector forceStorage; /**< Stores the accumulated forces within a frame. */

        public:
            /**
            * Returns the position of the particle.
            *
            * @return The position of the particle.
            */
            [[nodiscard]] Vector getPosition() const;

            /**
            * Sets the position of the particle using the given coordinates - x and y as scalar values.
            *
            * @param x The x-coordinate of the new position.
            * @param y The y-coordinate of the new position.
            */
            void setPosition(real x, real y);

            /**
            * Sets the position of the particle using the given coordinates - x and y as a vector.
            *
            * @param pos The vector representing the new position.
            */
            void setPosition(const Vector &pos);

            /**
            * Sets the velocity of the particle using the given vector.
            *
            * @param velocity The vector representing the new velocity.
            */
            void setVelocity(const Vector &velocity);

            /**
             * Sets the velocity of the particle using the given x and y values.
             *
             * @param x The x-coordinate of the new velocity.
             * @param y The y-coordinate of the new velocity.
             */
            void setVelocity(real x, real y);

            /**
            * Returns the velocity of the particle.
            *
            * @return The velocity of the particle.
            */
            [[nodiscard]] Vector getVelocity() const;

            /**
            * Sets the acceleration of the particle using the given vector.
            *
            * @param acc The vector representing the new acceleration.
            */
            void setAcceleration(const Vector &acc);

            /**
             * Sets the acceleration of the particle using the given x and y values.
             *
             * @param x The x-coordinate of the new acceleration.
             * @param y The y-coordinate of the new acceleration.
             */
            void setAcceleration(real x, real y);

            /**
             * Returns the acceleration of the particle.
             *
             * @return The acceleration of the Particle.
             */
            [[nodiscard]] Vector getAcceleration() const;

            /**
            * Sets the damping value for the particle (value between 0 and 1).
            * During the integration this value is used to reduce the velocity of the particle.
            * The closer the value is to 1, the less the velocity will be reduced.
            *
            * @param value The damping value to set.
            */
            void setDamping(real value);

            /**
             * Returns the inverted mass of the particle.
             *
             * @return The inverted mass of the particle.
             */
            [[nodiscard]] real getInvertedMass() const;

            /**
            * Sets the mass of the particle. The value is stored as 1/mass.
            * The mass value must be greater than 0. When 0 is passed, the mass is set to infinity,
            * which is useful for static objects.
            *
            * @param mass The mass value to set.
            */
            void setMass(real mass);

            /**
            * Performs integration using a first-order numerical procedure for solving ordinary differential equations
            * (ODEs) - the Euler method. The position and velocity of the particle are updated using the current
            * acceleration, forces and damping values. The integration is performed using the given time step.
            *
            * @param delta The time step for the integration.
            */
            void integrate(real delta);

            /**
            * Adds a given force to the force storage.
            *
            * @param force The force vector to add.
            */
            void addForce(Vector force);

            /**
             * Clear the storage from accumulated forces
             * */
            void clearForceStorage();
        };
}

#endif //SIMPLE_PHYSICS_ENGINE_PARTICLE_H