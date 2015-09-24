/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include "pretty_type_print.hpp"

void foo(char *) {
    std::cout << "char * fct" << std::endl;
}
void foo(int) {
    std::cout << "int fct" << std::endl;
}

int main() {
    PRINT_TYPE_OF(0)       // int
    PRINT_TYPE_OF(NULL)    // long
    PRINT_TYPE_OF(nullptr) // decltype(nullptr) / very convenient :P
    
    foo(0);
    //~ foo(NULL); //ambiguous since decltype(NULL) == long
    foo(nullptr);
    
    return 0;
}
