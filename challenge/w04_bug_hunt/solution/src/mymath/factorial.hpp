/*******************************************************************************
 *
 * factorial Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <cstdint>

// precondition:  a positive number, whose factorial fits in the return type
// postcondition: the factorial of the number
unsigned int factorial_take1(unsigned int);

// precondition:  a positive number
// postcondition: the factorial of the number if fits the return type
//                otherwise a std::logic_error is thrown
uint32_t factorial_take2(uint32_t);
