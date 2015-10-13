/*******************************************************************************
 * 
 * advanced examples about the vtable
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <typeinfo>

// a method pointer is a pair of integers and not an address

// if the method is virtual:
// the second number stores the offset to the vtbl-ptr in the instance 
// (see base_slicing.cpp) and the first number the location of the method 
// in the vtbl. we're not sure why it starts at 1 instead of 0...
// 
// if the method is not virtual:
// first number is the address as for any function pointer
// second number is probably irrelevant


struct uint128_t {  // pair of address type sized integers
    uint64_t hi;
    uint64_t lo;
};

struct B {
    virtual void foo(){std::cout << "base foo" << std::endl;}
    virtual void bar(){std::cout << "base bar" << std::endl;}
    int64_t x;
};

struct B2 {
    virtual void baz() {std::cout << "base2 baz" << std::endl;}
    int64_t y;
};

struct B3 {
    void fob() {std::cout << "base3 fob" << std::endl;}
};

struct D: public B, B2, B3 {
    virtual void bar() override {std::cout << "deri bar" << std::endl;}
    
    int64_t z;
};

template<typename T>
void report_method(void (T::*t)(), std::string const & name) {
    
    uint128_t * ad = (uint128_t*)&t;
    
    std::cout << std::setbase(10)
              << typeid(T).name() << "::" << name 
              << " hi/lo: "<< ad->hi << " "
              << ad->lo
              << std::setbase(10) << std::endl;
}

int main(){
    
    report_method<B>(&B::foo, "foo");
    report_method<B>(&B::bar, "bar");
    report_method<D>(&D::foo, "foo");
    report_method<D>(&D::bar, "bar");
    report_method<D>(&D::baz, "baz"); // 16 offset (8 vtbl-ptr of B + 8 B.x)
    report_method<D>(&D::fob, "fob"); // returns address instead of offset
    
    std::cout << "\033[1;32m" << "---checkpoint 1---" << "\033[0m" << std::endl;
    report_method(&D::foo, "foo"); // deduces B
    report_method(&D::baz, "baz"); // deduces B2
    
    
    return 0;
}
