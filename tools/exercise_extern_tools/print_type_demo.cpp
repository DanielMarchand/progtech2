// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.10.2015 23:50:00 CEST
// File:    print_type_demo.cpp

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
