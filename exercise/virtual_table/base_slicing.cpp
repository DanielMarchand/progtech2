/*******************************************************************************
 * 
 * advanced examples about the vtable
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>

// Demonstrates how different base-pointer of an object (multiple inheritance)
// point to different places in the object itself (base-slicing)

struct B {
    virtual void foo() {}
    uint64_t x;
};

struct B2 {
    virtual void bar() {}
    uint64_t y;
};

struct B3 {
    char y;
};


struct D: public B, public B2, public B3 {
    uint64_t z;
};

int main(){
    D d;
    
    /*
    Layout of d:
    ---------------------+
    0   : vtbl-ptr to B  | <== dpB <== dpD
    8   : x              |
    ---------------------+
    16  : vtbl-ptr to B2 | <== dpB2
    24  : y              | padded to addressing type size (64bit == 8 bytes)
    ---------------------+
    32  : y              | <== dpB3 (without vtbl)
    ---------------------+
    40  : z              |
    ---------------------+
    */
    
    D * dpD = &d;
    B * dpB = &d;   // same value as dpD because first in inheritance list
    B2 * dpB2 = &d; // implicit slice / not the same value as dpD!!!
    B3 * dpB3 = &d; // same here (different location)
    
    std::cout << "dpD: " << dpD << std::endl;
    std::cout << "dpB-dpD:     " << uint64_t(dpB) - uint64_t(dpD) << std::endl;
    std::cout << "dpB2-dpD:    " << uint64_t(dpB2) - uint64_t(dpD) << std::endl;
    std::cout << "d.B2::y-dpD: " << uint64_t(&d.B2::y) - uint64_t(dpD) << std::endl;
    std::cout << "dpB3-dpD:    " << uint64_t(dpB3) - uint64_t(dpD) << std::endl;
    std::cout << "d.z-dpD:     " << uint64_t(&d.z) - uint64_t(dpD) << std::endl;
    
    
    return 0;
}
