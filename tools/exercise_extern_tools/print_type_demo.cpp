/*******************************************************************************
 *
 * Demo of the type printing macros.
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>

#include "../../exercise/extern/include/util/print_type.hpp"

template<typename T>
void fct(T && t) {
    std::cout << fct_sig() << std::endl;
    PRINT_TYPE(T)
    PRINT_TYPE_OF(t)
}

int main() {
    
    int a;
    
    PRINT_TYPE_OF(a)
    PRINT_TYPE_OF(std::move(a))
    
    fct(a);
    fct(std::move(a));
    
    return 0;
}
