//
// Created by dave on 27.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_VECTOR_H
#define SIMPLE_PHYSICS_ENGINE_VECTOR_H

#include <cmath>
#include "precision.h"

namespace engine {
    /**
     * Represents a vector in two dimensions. Allows for basic vector operations, such as addition, subtraction,
     * scaling, component product, and cross product. These operations are used to calculate forces, velocities, and
     * positions of objects in the simulation.
     */
    class Vector {
        public:
            real x; /**< Stores the value of x axis */
            real y; /**< Stores the value of y axis */

            /** The default constructor creates a new vector with x and y coordinates with default values (0.0f, 0.0f) */
            Vector() : x(0.0f), y(0.0f) {}

            /**
             * The explicit constructor creates a vector with the given values for x and y.
             *
             * @param x The value of x axis.
             * @param y The value of y axis.
             * */
            Vector(const real x, const real y) : x(x), y(y) {}

            /**
             * Inverts the vector by changing the sign of both components.
             * Used to change direction of a Vector while keeping the magnitude.
             * */
            void invert() {
                x = -x;
                y = -y;
            }

            /**
             * Returns the length of a vector that represents the distance from origin to the endpoint.
             * Magnitude is calculated by taking the square root of the sum of the squares of the vector's components.
             *
             * @return The magnitude of the stored vector.
             * */
            [[nodiscard]] real getMagnitude() const {
                return real_sqrt(x*x+y*y);
            }

            /**
             * Returns the squared length of a vector that represents the distance from origin to the endpoint.
             * Magnitude is calculated by taking the sum of the squares of the vector's components.
             *
             * @return The squared magnitude of the stored vector.
             * */
            [[nodiscard]] real getSquaredMagnitude() const {
                return x*x+y*y;
            }

            /**
             * Performs a normalization on the vector.
             * It is performed by dividing each component of a vector by the magnitude.
             * */
            void normalize() {
                real magnitude = getMagnitude();

                // Avoid dividing by zero
                if(magnitude > 0.0f) {
                    x /= magnitude;
                    y /= magnitude;
                }
            }

            /**
             * Divides each component of the stored vector by the given scalar.
             *
             * @param value The scalar value to divide the vector by.
             */
            void operator/=(const real value) {
                x /= value;
                y /= value;
            }

            /**
             * Multiplies each component of the stored vector by the given scalar.
             *
             * @param value The scalar value to multiply the vector by.
             */
            void operator*=(const real value) {
                x *= value;
                y *= value;
            }

            /**
             * Returns a copy of the stored vector, scaled by the given value.
             *
             * @param value The scalar value to scale the vector by.
             * @return The scaled vector.
             */
            Vector operator*(const real value) const {
                return Vector{x*value, y*value};
            }

            /**
            * Adds the given vector to the stored vector.
            *
            * @param vector The vector to add to the stored vector.
            */
            void operator+=(const Vector& vector) {
                x += vector.x;
                y += vector.y;
            }

            /**
             * Returns a copy of the stored vector increased by the given vector.
             *
             * @param vector The vector to add to the stored vector.
             * @return The resulting vector.
             */
            Vector operator+(const Vector& vector) const {
                return {x + vector.x, y + vector.y};
            }

            /**
             * Subtracts the given vector from the stored vector.
             *
             * @param vector The vector to subtract from the stored vector.
             */
            void operator-=(const Vector& vector) {
                x -= vector.x;
                y -= vector.y;
            }

            /**
             * Returns a copy of the stored vector decreased by the given vector.
             *
             * @param vector The vector to subtract from the stored vector.
             * @return The resulting vector.
             */
            Vector operator-(const Vector& vector) const {
                return {x - vector.x, y - vector.y};
            }

            /**
             * Adds a scaled version of the given vector to the stored vector.
             *
             * @param vector The vector to scale and add to the stored vector.
             * @param scale The scalar value to scale the given vector by.
             */
            void addScaledVector(const Vector& vector, real scale) {
                x += vector.x * scale;
                y += vector.y * scale;
            }

            /**
             * Calculates and returns the scalar product of the stored vector with the given vector.
             *
             * @param vector The vector to calculate the scalar product with.
             * @return The scalar product of the stored vector with the given vector.
             */
            [[nodiscard]] real getScalarProduct(const Vector &vector) const {
                return x * vector.x + y * vector.y;
            }

            /** Returns a component product of the stored vector with the given vector.
             *
             * @param vector The vector to calculate the component product with.
             * @return The component product of the stored vector with the given vector.
             * */
            [[nodiscard]] Vector getComponentProduct(const Vector &vector) const {
                return {x * vector.x, y * vector.y};
            }

            /**
             * Calculates a component product of the stored vector with a given vector and sets the stored vector
             * to its result.
             *
             * @param vector The vector to calculate the component product with.
             */
            void updateComponentProduct(const Vector &vector) {
                x *= vector.x;
                y *= vector.y;
            }
    };
}

#endif //SIMPLE_PHYSICS_ENGINE_VECTOR_H