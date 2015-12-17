// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:31:05 CET
// File:    04_uncaught_exception.cpp

#include <iostream>


struct foo {
    ~foo() {
        std::cout << std::uncaught_exception() << std::endl; // c++14 true or false
        std::cout << std::uncaught_exceptions() << std::endl; // c++17 amount of active exceptions
    }
};


int main() {
    try {
        foo f;
        throw std::runtime_error("bla");
    } catch(...) {}
    
    return 0;
}
