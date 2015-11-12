// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 23:06:49 CET
// File:    08_back_in_time.cpp

#include <iostream>

//=================== divides ===================
template<int candidate, int div>
struct divides {
    enum {value = (candidate % div == 0)};
};

//=================== is_prime ===================
// recursion for prime
/* for(i = idx; idx < max; ++i) 
 *     if(divisible(candidate, idx))
 *         return false;
 * return true;
 */
template<int candidate, int idx, int max, bool = false>
struct is_prime_rec {
    static const bool div = divides<candidate, idx>::value;
    enum {value = is_prime_rec<candidate, idx+1, max, div>::value};
};
// if divisible
template<int candidate, int idx, int max>
struct is_prime_rec<candidate, idx, max, true> {
    enum {value = false};
};

// if end of iteration, max reached
template<int candidate, int max, bool div>
struct is_prime_rec<candidate, max, max, div> {
    enum {value = true};
};

template<int candidate>
struct is_prime {
    enum {value = is_prime_rec<candidate, 2, candidate>::value};
};

//=================== calc_lpb ===================
/*
 * if(is_prime(candidate))
 *     return candidate
 * else
 *     return is_prime(candidate - 1)
 */
template<int candidate, bool = false>
struct calc_lpb_rec {
    static const bool prime = is_prime<candidate>::value;    
    enum {value = calc_lpb_rec<candidate - 1, prime>::value };
};

template<int candidate>
struct calc_lpb_rec<candidate, true> {
    enum {value = candidate + 1};
};

template<int N>
struct calc_lpb {
    enum {value = calc_lpb_rec<N-1>::value};
};

// C++98 version
template<int N>
struct largest_prime_below {
    enum {value = calc_lpb<N>::value};
};

int main() {
    // don't modify the main
    
    const int N = 100;  // this could be arbitrary
    //~ const int N = 10;  // this could be arbitrary
        
    // since there is no constexpr in c++98/03, we emulate it with array size
    int a[largest_prime_below<N>::value];
    (void)a; // omit the "unused variable" warning
    
    std::cout << largest_prime_below<N>::value << std::endl;
    
    return 0;
}
