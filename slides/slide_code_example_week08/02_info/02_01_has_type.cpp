// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 23:10:31 CET
// File:    02_01_has_type.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <vector>
#include <type_traits> // true / false_type

//=================== has_size_type ===================
template<typename T>
struct has_size_type {

    template<typename U>
    static std::true_type check(typename U::size_type * i);
    
    template<typename U>
    static std::false_type check(...); // just catch anything else (variadic function)
    
    static constexpr bool value = decltype(check<T>(nullptr))::value;
};
//============== a type that has a typedef size_type ==============
struct foo {
    using size_type = int;
};

struct bar {
    
};

//=================== main ===================
int main() {
    
    PNW_BOOL(has_size_type<bar>::value)
    
    PNW_BOOL(has_size_type<foo>::value)
    
    PNW_BOOL(has_size_type<int>::value)
    
    PNW_BOOL(has_size_type<std::vector<int>>::value)
    
    PW_YELLOW("we can find out if a type contains a typedef")
    
    return 0;
}
