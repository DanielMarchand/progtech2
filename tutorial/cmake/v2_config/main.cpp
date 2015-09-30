// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    14.07.2012 10:23:23 CEST
// File:    main.cpp

#include <iostream>
#include <cmath>

#include "tutorial_config.hpp"

int main(int argc, char* argv[])
{
    // all @var@ from CMakeList.txt are saved according to TutorialConfig.hpp.in 
    // to global variables
    std::cout << "the current version is: v" << v_major << "." << v_minor << std::endl;
    
    double a = input_nr;
    std::cout << "the number is: " << a << std::endl;
    std::cout << "the sqrt is:   " << sqrt(a) << std::endl;
    
    return 0;
}
