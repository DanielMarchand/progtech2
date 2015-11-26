/*******************************************************************************
 * 
 * Initializer Order
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>

// meta integer
template<int N>
struct m_int {
    static constexpr int nr = N;
};

// every time I call it, it returns 10 more
int cnt() {
    static int idx = -10;
    idx += 10;
    return idx;
}

template<typename T>
int add_nr() {
    return T::nr + cnt();
}

struct pass {
    // variadic ctor
    template<typename... TN>
    pass(TN...) {
    }
};

template<typename... T>
void incr_and_print() {
    
    auto print = [](int const & nr){ std::cout << nr << std::endl; return 0; };
    // return 0 is the "cost" for this trick
    
    pass(print(add_nr<T>())...); // random order of function argument init
    //~ pass{print(add_nr<T>())...}; // "initializer list" ctor, respects order
}

void print(int a, int b, int c, int d) {
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
}

int main() {
    
    // what we want:
    std::cout << add_nr<m_int<1>>() << std::endl;
    std::cout << add_nr<m_int<2>>() << std::endl;
    std::cout << add_nr<m_int<3>>() << std::endl;
    std::cout << add_nr<m_int<4>>() << std::endl;
    // ... could go on, we need variadic templates
    
    // problem with "random" fct arg eval
    print(cnt(), cnt(), cnt(), cnt());
    
    // variadic solution
    incr_and_print<m_int<1>, m_int<2>, m_int<3>, m_int<4>>();
    
    return 0;
}
