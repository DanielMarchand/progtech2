// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 23:06:49 CET
// File:    08_back_in_time.cpp

#include <iostream>

//=================== divides ===================
constexpr bool divides(int const & candidate, int const & div) {
    return candidate % div == 0;
}

//=================== is_prime ===================
constexpr bool is_prime_rec(int const & candidate
                          , int const & idx
                          , int const & max) {
    return idx == max ? true : 
        (divides(candidate, idx) ? false : is_prime_rec(candidate, idx+1, max));
}

constexpr bool is_prime(int const & candidate) {
    return is_prime_rec(candidate, 2, candidate);
}

//=================== calc_ldb ===================
constexpr int calc_lpb_rec(int const & candidate) {
    return is_prime(candidate) ? candidate : calc_lpb_rec(candidate - 1);
}

constexpr int calc_lpb(int const & N) {
    return calc_lpb_rec(N-1);
}

// C++11 version
template<int N>
struct largest_prime_below {
    static constexpr int value = calc_lpb(N);
};

int main() {
    // don't modify the main
    
    const int N = 100;  // this could be arbitrary
    //~ const int N = 97;  // this could be arbitrary
    
    // since there is no constexpr in c++98/03, we emulate it with array size
    int a[largest_prime_below<N>::value];
    (void)a; // omit the "unused variable" warning
    
    std::cout << largest_prime_below<N>::value << std::endl;
    
    return 0;
}
