// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 10:48:27 CET
// File:    02_05_plus_automatic.cpp


//=================== include ===================
#include "../presentation.hpp"
#include <type_traits> // true / false_type

//=================== trait ===================
template<typename T>
struct has_plus_trait {
    // we use SFINAE in the default argument for S
    template<typename U
           , typename S = decltype(std::declval<U>() + std::declval<U>())>
    static std::true_type check(int);
    
    template<typename U>
    static std::false_type check(...);
    
    static constexpr bool value = decltype(check<T>(0))::value;
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

//=================== main ===================
int main() {
    
    CNWW_YELLOW(fct(1, 1))
    
    CNWW_YELLOW(fct("a", "b"))
    
    CNWW_YELLOW(fct(1.1, 1.1))
    
    PW_GREEN("now we don't need to specialize traits anymore")
    PW_YELLOW("there are still valid reasons to use traits")
    PW_RED("but only use them if necessary, otherwise query yourself")
    
    return 0;
}
