/*******************************************************************************
 *
 * factorial_take2 Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <limits>
#include <stdexcept>

#include "factorial.hpp"

// see documentation in .hpp
uint32_t factorial_take2(uint32_t number) {
    uint32_t res = 1;
    
    for(uint8_t i = 1; i <= number; ++i) {
        res *= i;
        if(double(res)*i > std::numeric_limits<uint32_t>::max())
            throw std::runtime_error("overflow");
    }
    return res;
}
