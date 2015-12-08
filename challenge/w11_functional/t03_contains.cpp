/*
 * Check if a list contains a value
 * Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
 * Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * compile with (CC e.g. gcc or clang)
 *   CC -o t03_contains t03_contains.cpp
 */

#include <type_traits>
#include <iostream>

template<int N, int... Rest>
struct contains : std::true_type {};

template<int N>
struct contains<N> : std::false_type {};

template<int N, int M, int... Rest>
struct contains<N, M, Rest...> :
    std::conditional<N == M,
        std::true_type,
        contains<N, Rest...>
    >::type {};

// let's not fuss around with randomly generating metatemplate lists ;)
#define LIST 2,66,80,12,81,13,48,78,66,4,62,88,71,16,99,82,23,56,19,90,5,88,63,\
    10,35,28,75,16,50,60,50,8,40,47,4,41,17,36,97,63,92,13,76,27,7,75,3,26,70, \
    10,4,83,50,15,94,99,25,48,7,38,38,47,21,4,51,67,62,56,42,55,70,75,29,13,28,\
    20,36,79,55,41,37,23,7,96,16,28,80,59,13,48,80,58,41,91,95,30,4,0,94,37,59,\
    50,85,38,10,32,94,46,35,68,60,94,35,5,61,90,9,40,4,34,65,64,57,16,7,27,6,4,\
    6,97,10,7,46,79,0,17,8,6,34,73,36,49,77,78,84,0,1,15,74,19,31,40,4,17,14,  \
    71,59,7,43,37,24,94,43,63,38,21,35,11,38,59,99,10,69,0,88,20,76,74,29,67,  \
    99,93,64,9,49,26,73,82,43,20,93,0,76,89,90,60,73,61,28,81

int main() {

    auto b = contains<42, LIST>() ? "in list" : "not in list";
    std::cout << b << std::endl;
    b = contains<44, LIST>() ? "in list" : "not in list";
    std::cout << b << std::endl;

    return 0;

}
