/*******************************************************************************
 * 
 * Week 04 Exception Safety Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>
#include <stdexcept>

class X {
public:
    // structors
    ~X() {
        std::cout << "X dtor" << std::endl;
        // comment/uncomment the following line
        //~ throw std::runtime_error("oops"); // welcome to hell
    }
};

void f() {
    X a;
    // comment/uncomment the following line
    //~ throw std::runtime_error("oops"); // this can be caught
}

int main(){
    
    try {
        f();
        std::cout << "no throw" << std::endl;
    } catch(...) {
        std::cout << "catch successful" << std::endl;
    }
    
    return 0;
}
