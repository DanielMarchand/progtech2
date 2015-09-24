/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>


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
    
    // c++11: decltype returns the exact type of the object it takes
    decltype(num)    d0 = num;
    decltype(num_r)  d1 = num_r;
    decltype(num_c)  d2 = num_c;
    decltype(num_cr) d3 = num_cr;
    
    PRINT_TYPE_OF(d0)
    PRINT_TYPE_OF(d1)
    PRINT_TYPE_OF(d2)
    PRINT_TYPE_OF(d3)
    
    // c++14: use "decltype type deduction" 
    // instead of "template type deduction" for auto
    decltype(auto) a0 = num;
    decltype(auto) a1 = num_r;
    decltype(auto) a2 = num_c;
    decltype(auto) a3 = num_cr;
    
    PRINT_TYPE_OF(a0)
    PRINT_TYPE_OF(a1)
    PRINT_TYPE_OF(a2)
    PRINT_TYPE_OF(a3)
    
    return 0;
}
