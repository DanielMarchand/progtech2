/*******************************************************************************
 *
 * PennaLV Simulation Code
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved. <- use license (discussion)
 *
 ******************************************************************************/

#include <iostream>
#include <limits>
#include <mymath/factorial.hpp>
#include <mymath/point_take1.hpp>
#include <mymath/point_take2.hpp>

int main() {
    std::cout << factorial_take1(15) << std::endl;
    std::cout << factorial_take2(11) << std::endl;
    std::cout << std::numeric_limits<uint32_t>::max() << std::endl;
    std::cout << sizeof(int) << std::endl;
    point_take1 p(1, 2);
    
    std::cout << p << std::endl;
    
    return 0;
}

