I/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include <type_traits>
#include "pretty_type_print.hpp"


// first try -> bad if T = int
template<typename T>
T mean_try1(T const & a, T const & b) {
    return (a + b) / 2.0;
}

// try two -> bad for floating types with 
// higher or lower precision that double
template<typename T>
double mean_try2(T const & a, T const & b) {
    return (a + b) / 2.0;
}

// try three -> doesn't work with my_int
template<typename T, bool is_integral>
struct mean_trait {
    typedef double type;
};

template<typename T> // use partial template specialisation
struct mean_trait<T, false> {
    typedef T type;
};

// isn't it a thing of beauty...
template<typename T>
typename mean_trait< T
                   , std::is_integral<T>::value
                   >::type mean_try3(T const & a, T const & b) {
    return (a + b) / 2.0;
}

// take 4, fully generic (after this you'll love decltype)
template<typename T>
struct use_double_identifier {
    static T t;
    
    static char check(T);
    static double check(double);
    
    enum {value = (sizeof(check((t+t)/double(2))) == sizeof(double))};
};
 // full specialization
template<>
struct use_double_identifier<double> {
    enum {value = true}; //doesn't matter if true or false
};


template<typename T, bool use_double> //default true
struct better_mean_trait_chooser {
    typedef double type;
};

template<typename T>
struct better_mean_trait_chooser<T, false> {
    typedef T type;
};

// better mean_trait
template<typename T>
struct better_mean_trait {
    typedef 
        typename 
            better_mean_trait_chooser<T, use_double_identifier<T>::value
        >::type
    type;
};

template<typename T>
typename better_mean_trait<T>::type mean_try4(T const & a, T const & b) {
    return (a + b) / 2.0;
}

// try 5 with decltype in front 
// declval fakes an instanciation, since I have no clue how to construct T
template<typename T>
decltype((std::declval<T>() 
        + std::declval<T>()) 
        / double()) mean_try5(T const & a, T const & b) {
    return (a + b) / 2.0;
}

// try 6 with trailing return type (just nicer syntax, identical to try5)
template<typename T>
auto mean_try6(T const & a, T const & b) -> decltype((a+b)/2.0) {
    return (a + b) / 2.0;
}

// try 7 c++14 return value deduction
/*
template<typename T>
decltype(auto) mean_try7(T const & a, T const & b) {
    return ((a + b) / 2.0);
}
*/

// my custom integer struct
struct my_int {
    my_int(int const & in): x(in) {
    }
    int x;
};
my_int operator+(my_int const & a, my_int const & b) {
    return my_int(a.x + b.x);
}
double operator/(my_int const & a, double const & d) {
    return a.x / d;
}


int main() {
    
    auto try1 = mean_try1(1, 2); // == 1 bad...
    PRINT_TYPE_OF(try1)
    std::cout << try1 << std::endl;
    
    auto try2 = mean_try2(float(1), float(2)); // returns double / too precise
    PRINT_TYPE_OF(try2)
    std::cout << try2 << std::endl;
    
    auto try3 = mean_try3(float(1), float(2)); // only catches std::integral types
    PRINT_TYPE_OF(try3)
    std::cout << try3 << std::endl;
    
    auto try3b = mean_try3(my_int(1), my_int(2)); // fails
    PRINT_TYPE_OF(try3b)
    std::cout << try3b.x << std::endl;
    
    auto try4 = mean_try4(my_int(1), my_int(2)); // trylso works with my_int, still not perfect...
    PRINT_TYPE_OF(try4)
    std::cout << try4 << std::endl;
    
    auto try5 = mean_try5(my_int(1), my_int(2)); // works for everything
    PRINT_TYPE_OF(try5)
    std::cout << try5 << std::endl;
    
    // try 6 & try 7 only differ in syntax
    
    return 0;
}
