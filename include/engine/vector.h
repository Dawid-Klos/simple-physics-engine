//
// Created by dave on 27.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_VECTOR_H
#define SIMPLE_PHYSICS_ENGINE_VECTOR_H

#include <cmath>
#include "precision.h"

namespace engine {
    /** Represents a vector in three dimensions - x, y, z. */
    class Vector {
    public:
        real x; /** Holds the value of x axis */
        real y; /** Holds the value of y axis */
        real z; /** Holds the value of z axis */

        /** The default constructor creates a new vector */
        Vector() : x(0), y(0), z(0) {}

        /** The explicit constructor creates a vector with the given values */
        Vector(const real x, const real y, const real z) : x(x), y(y), z(z) {}

        /** Inverts all the values of the stored vector */
        void invert() {
            x = -x;
            y = -y;
            z = -z;
        }

        /** Returns the magnitude of the stored vector */
        [[nodiscard]] real getMagnitude() const {
            return real_sqrt(x*x+y*y+z*z);
        }

        /** Returns the squared magnitude of the stored vector */
        [[nodiscard]] real getSquaredMagnitude() const {
            return x*x+y*y+z*z;
        }

        /** Perform a normalization on a vector */
        void normalize() {
            real magnitude = getMagnitude();

            /* Avoid dividing by zero */
            if(magnitude > 0) {
                (*this).x /= magnitude;
                (*this).y /= magnitude;
                (*this).z /= magnitude;
            }
        }

        /** Multiplies the stored vector by the given scalar */
        void operator*=(const real value) {
            x *= value;
            y *= value;
            z *= value;
        }

        /** Return a copy of the stored vector, scaled by a given value */
        Vector operator*(const real value) const {
            return Vector{x*value, y*value, z*value};
        }

        /** Adds given vector as parameter to the stored vector */
        void operator+=(const Vector& vector) {
            x += vector.x;
            y += vector.y;
            z += vector.z;
        }

        /** Returns a copy of the stored vector increased by a given vector */
        Vector operator+(const Vector& vector) const {
            return {x + vector.x, y + vector.y, + z + vector.z};
        }

        /** Subtracts given vector from the stored vector */
        void operator-=(const Vector& vector) {
            x -= vector.x;
            y -= vector.y;
            z -= vector.z;
        }

        /** Returns a copy of the stored vector decreased by a given vector */
        Vector operator-(const Vector& vector) const {
            return {x - vector.x, y - vector.y, z - vector.z};
        }

        /** Adds the given vector to stored vector, scaled by the given amount. */
        void addScaledVector(const Vector& vector, real scale) {
            x += vector.x * scale;
            y += vector.y * scale;
            z += vector.z * scale;
        }

        /**
         * Calculates and returns the scalar product of stored vector
         * with the given vector.
         */
        [[nodiscard]] real getScalarProduct(const Vector &vector) const {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        /**
        * Returns a component product of the stored vector with the given vector
        */
        [[nodiscard]] Vector getComponentProduct(const Vector &vector) const {
            return {x * vector.x, y * vector.y, z * vector.z};
        }

        /**
         * Calculates a component product of the stored vector with a given
         * and sets the stored vector to its result
         */
        void updateComponentProduct(const Vector &vector) {
            x *= vector.x;
            y *= vector.y;
            z *= vector.z;
        }
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_VECTOR_H
