// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 10:48:27 CET
// File:    01_01_plus_trait.cpp


//=================== include ===================
#include "../presentation.hpp"
#include <stdexcept>

//=================== trait ===================
template<typename T>
struct has_plus_trait {
    static constexpr bool value = false;
};

// we need to specialize our trait for 
// every type that supports addition
template<> // full spec
struct has_plus_trait<int> {
    static constexpr bool value = true;
};

//=================== trait dependent implementation ===================
// std::enable_if_t<bool B, typename T = void>
// is T if B is true, and will fail to substitute otherwise (SFINAE)

template<typename T>
std::enable_if_t<has_plus_trait<T>::value> fct(T const & a, T const & b) {
    std::cout << a << " + " << b << " = " << a + b << std::endl;
}

template<typename T>
std::enable_if_t<!has_plus_trait<T>::value> fct(T const & a, T const & b) {
    std::cout << "I dont know how to add " << a << " and " << b << std::endl;
}

//~ void fct(double const &, double const &) {
    //~ throw std::runtime_error("we dont like doubles");
//~ }

//=================== main ===================
int main() {
    
    CNWW_YELLOW(fct(1, 1))
    
    CNWW_YELLOW(fct("a", "b"))
    
    CNWW_YELLOW(fct(1.1, 1.1))
    
    PW_GREEN("traits can tell an algorithm how to use a ceratin type")
    PW_YELLOW("if the algorithm is completely off for a type")
    P_YELLOW("just overload the algoritm for this type")
    
    return 0;
}
