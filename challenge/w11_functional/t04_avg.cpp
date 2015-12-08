/*
 * Compute the average of a list
 * Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
 * Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
 *
 * compile with (CC e.g. gcc or clang)
 *   CC -std=c++11 -o t04_avg t04_avg.cpp
 */

#include <array>
#include <iostream>
#include <iterator>

/*******************************************************************************
 * List generator
 */

// so random!
constexpr int super_random(int n) {
  return ((n+23)*(n+29))%100;
}
// return a std::array of size N

template<int N, int... VAL>
constexpr typename std::enable_if<N == sizeof...(VAL), std::array<int, N>>::type
rlist() {
    return std::array<int, N>{VAL...};
}

// build up to N VALs
template<int N, int... VAL>
constexpr typename std::enable_if<N != sizeof...(VAL), std::array<int, N>>::type  // no enable_if_t ;(
rlist() {
    return rlist<N, super_random(sizeof...(VAL)), VAL...>();  
}

/*******************************************************************************
 * Average calculator
 */

template<unsigned long N>
constexpr double average_impl(const std::array<int, N> a, const int cnt) {
    return cnt==0 ? a[cnt] : a[cnt] + average_impl(a, cnt-1);
}

template<unsigned long N>
constexpr double average(std::array<int, N> a) {
    return average_impl(a, N-1) / N;
}

/*******************************************************************************
 * Main
 */

int main() {

    constexpr std::array<int, 4> a = {1,2,3,4};
    constexpr double avg = average(a);
    std::cout << avg << std::endl;

    constexpr auto longlist = rlist<200>();
    constexpr double avg2 = average(longlist);
    std::cout << avg2 << std::endl;
    //~ std::copy(std::begin(longlist), std::end(longlist), std::ostream_iterator<int>(std::cout, " "));

    return 0;

}
