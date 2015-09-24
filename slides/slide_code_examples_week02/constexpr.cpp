/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include <array> //int a[10] is not needed anymore

constexpr int add(int a, int b) {
    return a + b;
}

// c++11 only allows one return in a constexpr function
// "for" loops -> recursions
constexpr int pow(int a, int b) {
    return b == 0 ? 1 : pow(a, b - 1) * a;
}

//~ // c++14 relaxes the constrains for constexpr functions
constexpr int pow2(int a, int b) {
    int res = 1;
    for(int i = 0; i < b; ++i) {
        res *= a;
    }
    return res;
}

int main(int argc, char* argv[]) {
        
    // the size needs to be knows during compiletime
    std::array<int, 10> a;

    // this fails
    //~ int n = 10;
    //~ int const N = n;
    //~ std::array<int, N> b;
    
    // this works (the compiler checks if a const is known at compile-time)
    int const N1 = 10;
    // maybe N1 is known, maybe it isn't, let's try
    std::array<int, N1> c;

    // this works
    int constexpr N2 = 10;
    // N2 is guaranteed to be known during compile-time
    std::array<int, N2> d;

    // add is executed during compiletime 
    // if the result used in a constexpr context
    std::array<int, add(1, N2)> e;

    int n1;
    int n2;

    std::cin >> n1;
    std::cin >> n2;

    // a constexpr fct behaves like a 
    // normal function during runtime
    std::cout << add(n1, n2) << std::endl;
    std::cout << pow(2, 10) << std::endl;
    //~ std::cout << pow2(2, 10) << std::endl;


    return 0;
}
