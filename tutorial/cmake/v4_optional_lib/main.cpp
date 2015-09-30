// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    14.07.2012 10:23:23 CEST
// File:    main.cpp

#include <iostream>

#include <tutorial_config.hpp>

#ifdef USE_MYSQRT
    #include <my_sqrt.hpp>
#else
    #include <cmath>
#endif

int main() {
    double a = 9;
    std::cout << "the number is:  " << a << std::endl;
    #ifdef USE_MYSQRT
        std::cout << "the my_sqrt is: " << my_sqrt(a) << std::endl;
    #else
        std::cout << "the sqrt is:    " << sqrt(a) << std::endl;
    #endif
    
    return 0;
}
