/*******************************************************************************
 * 
 * Initializer Order
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>
#include <vector>
#include "../../exercise/extern/include/util/print_type.hpp"

void log_message(int const & nr) {
    std::cout << nr << " was assigned" << std::endl;
}

struct int_proxy {
    // support ctor (construct like an int)
    int_proxy(int const & nr): nr(nr) {
        log_message(nr);
    }
    
    // support implicit conversion (behave like an int)
    operator int() {
        return nr;
    }
    
    int nr; // wrap the object
};

int main() {
    
    // what we want
    int a = 10;
    log_message(a); // we dont want to type this
    
    // with proxy
    int_proxy b = 10;
    a = b; // behave like an int
    
    // proxies in stl
    std::vector<int> vi(1);
    std::vector<bool> vb(1);
    
    PRINT_TYPE_OF(vi[0])
    PRINT_TYPE_OF(vb[0])
    
    return 0;
}
