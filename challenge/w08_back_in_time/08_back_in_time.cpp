// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 23:06:49 CET
// File:    08_back_in_time.cpp

#include <iostream>

// c++14 version
constexpr int calc_lpb(int const & N) {
    int candidate = N - 1; // N excluded
    bool prime = true;
    
    for(; candidate > 1; --candidate) {
        prime = true;
        // going to sqrt(candidate) would be enough...
        // ... but have fun impl compiletime sqrt under c++98/03 :P
        for(int i = 2; i < candidate; ++i) {
            if(candidate % i == 0) {
                prime = false;
                break;
            }
        }
        if(prime)
            return candidate;
    }
}

// c++14 version
template<int N>
struct largest_prime_below {
    static constexpr int value = calc_lpb(N);
};

int main() {
    // don't modify the main
    
    const int N = 100;
    
    // since there is no constexpr in c++98/03 this emulates this
    int a[largest_prime_below<N>::value];
    (void)a; // so we dont get the unused variable warning
    
    std::cout << largest_prime_below<N>::value << std::endl;
    
    return 0;
}
