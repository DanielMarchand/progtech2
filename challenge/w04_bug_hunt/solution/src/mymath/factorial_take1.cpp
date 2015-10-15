/*******************************************************************************
 *
 * factorial_take1 Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "factorial.hpp"

// see documentation in .hpp
unsigned int factorial_take1(unsigned int number) {
    return number <= 1 ? number : factorial_take1(number - 1) * number;
}
