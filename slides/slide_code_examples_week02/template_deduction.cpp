/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include "pretty_type_print.hpp"

template<typename T>
void fct(T t_val) {
    PRINT_TYPE_OF(t_val);
}

template<typename T>
void fct_uref(T && t_uref) {
    PRINT_TYPE_OF(t_uref);
}

template<typename T>
void fct_ref(T & t_ref) {
    PRINT_TYPE_OF(t_ref);
}

int main() {
    int         num = 10;
    int &       num_r = num;
    int const   num_c = 10;
    int const & num_cr = num_c;
    
    PRINT_TYPE_OF(num)
    PRINT_TYPE_OF(num_r)
    PRINT_TYPE_OF(num_c)
    PRINT_TYPE_OF(num_cr)
    
    // pass by value
    fct(num);
    fct(num_r);
    fct(num_c);
    fct(num_cr);
    
    // pass by reference (or pointer, but not universal reference)
    fct_ref(num);
    fct_ref(num_r);
    fct_ref(num_c);
    fct_ref(num_cr);
    
    // pass by universal reference
    fct_uref(num);
    fct_uref(10);
    
    return 0;
}
