/*******************************************************************************
 * 
 * advanced examples about the vtable
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>

// side-note: O0 or O3 makes a large difference, since the compiler
//            optimizes away the vtbl-lookups

// DO NOT USE CODE LIKE THIS IN THE EXAM (or anywhere else) :D

struct B {
    virtual void foo(){std::cout << "base foo" << std::endl;}
    virtual void bar(){std::cout << "base bar" << std::endl;}
    void nonvirt(){std::cout << "nonvirt bar" << std::endl;}
    int64_t x;
};

struct D: public B {
    virtual void bar() override {std::cout << "deri bar" << std::endl;}
};

template<typename T>
void set_vtable(T const & t, uint64_t const & val) {
    uint64_t * ptr = (uint64_t*)&t;
    *ptr = val;
}

template<typename T>
uint64_t get_vtable(T const & t) {
    uint64_t * ptr = (uint64_t*)&t;
    return *ptr;
}

template<typename T>
void report(T const & t) {
    void*** ptr = (void***)&t;
    std::cout << "instance-size (byte): " << sizeof(T) << std::endl
              << "address of instance:  " << ptr << std::endl
              << "content of instance" <<  std::endl
              << "  vtbl-ptr: " << *ptr << std::endl
              << "  x:        " << *(ptr+1) << std::endl;
    
    std::cout << "address of vtable : " << *ptr << std::endl
              << "content of vtable"    << std::endl
              << "  address of foo :    " << *(*ptr) << std::endl
              << "  address of bar :    " << *(*ptr+1) << std::endl << std::endl;
    
}

int main(){
    B b;
    b.x = 5;
    report(b);

    D d;
    d.x = 7;
    report(d);
    //~ set_vtable(d, 0); // produces segfault on vtable-lookup
    
    B * bp = &b;
    b.bar();   // does not use the vtbl
    bp->bar(); // uses the vtbl (maybe only on -O0)
    
    D * dp = &d;
    d.bar();   // does not use the vtbl
    dp->bar(); // uses the vtbl (maybe only on -O0)
    
    std::cout << std::endl << "swap the vtbl for b & d" << std::endl;
    auto temp = get_vtable(b);
    set_vtable(b, get_vtable(d));
    set_vtable(d, temp);
    
    bp->bar(); // now uses D::bar (if -O0)
    dp->bar(); // now uses B::bar (if -O0)
    
    std::cout << std::endl;
    std::cout << "call via method-ptr" << std::endl;
    void (B::*fct)() = &B::bar; // method ptr always uses the vtbl (even on -O3)
    
    (d.*fct)();   // via (swapped) vtbl
    (dp->*fct)(); // via (swapped) vtbl 
    
    return 0;
}
