//
// Created by dave on 27.03.23.
//

#ifndef SIMPLE_PHYSICS_ENGINE_PRECISION_H
#define SIMPLE_PHYSICS_ENGINE_PRECISION_H

#include <cfloat>
// Code adapted from Millington, 2010
/**
 * Namespace engine contains all the classes and methods used to simulate physics.
 * It is used to avoid name collisions with other libraries.
 */
namespace engine {

    /**
     * Defines a real number precision. Allows to simply change the precision if needed.
     * By default single-precision is used.
     */
    typedef float real;

    /**
     * Defines the precision of the square root operator.
     */
    #define real_sqrt sqrt

    /**
     * Defines the precision of the power operator.
     */
    #define real_pow powf
}
// End of adapted code

#endif //SIMPLE_PHYSICS_ENGINE_PRECISION_H