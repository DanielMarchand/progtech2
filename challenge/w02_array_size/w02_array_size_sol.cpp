/*******************************************************************************
 * 
 * some challenge week 2 solutions
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <cstdint>

using uint = uint64_t; // since it is not available without an 
                       // include of certain libc-implementations

template<uint N>
constexpr uint array_size(int const (&)[N]) { // you dont need to (&name) the array
    return N;
}

template<typename A>
constexpr uint array_size2(A const & arr) { // less elegant but also ok
    return sizeof(arr) / sizeof(arr[0]);
}

int main() {
    constexpr uint N = 10; // for arbitrary N
    int a[N];
    constexpr uint size = array_size(a);
    
    if(size == N)
        return 0; // success
    return 1;     // array_size implementation not correct
}
