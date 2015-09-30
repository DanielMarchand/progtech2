// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    14.07.2012 10:23:23 CEST
// File:    main.cpp

#include <iostream>

#include <my_sqrt.hpp> // notice the global include style

int main() {
    double a = 9;
    std::cout << "the number is:  " << a << std::endl;
    std::cout << "the my_sqrt is: " << my_sqrt(a) << std::endl;
    
    return 0;
}
