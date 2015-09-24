/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include "pretty_type_print.hpp"

int main() {
    int         num = 10;
    int &       num_r = num;
    int const   num_c = 10;
    int const & num_cr = num_c;
    
    PRINT_TYPE_OF(num)
    PRINT_TYPE_OF(num_r)
    PRINT_TYPE_OF(num_c)
    PRINT_TYPE_OF(num_cr)
    
    // by value
    auto a0 = num;
    auto a1 = num_r;
    auto a2 = num_c;
    auto a3 = num_cr;
    
    PRINT_TYPE_OF(a0)
    PRINT_TYPE_OF(a1)
    PRINT_TYPE_OF(a2)
    PRINT_TYPE_OF(a3)
    
    // reference (or pointer, but not universal reference)
    auto & a0ref = num;
    auto & a1ref = num_r;
    auto & a2ref = num_c;
    auto & a3ref = num_cr;
    
    PRINT_TYPE_OF(a0ref)
    PRINT_TYPE_OF(a1ref)
    PRINT_TYPE_OF(a2ref)
    PRINT_TYPE_OF(a3ref)
    
    // universal reference
    auto && a0uref = num;
    auto && a1uref = 10;
    
    PRINT_TYPE_OF(a0uref)
    PRINT_TYPE_OF(a1uref)
    
    return 0;
}
