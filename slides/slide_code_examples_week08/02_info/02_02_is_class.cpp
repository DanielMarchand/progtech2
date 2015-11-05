// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 23:23:30 CET
// File:    02_02_is_class.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <type_traits> // true / false_type

//=================== is_class trait ===================
template<typename T> 
struct is_class {
    //second templates is needed since U::* is illegal for non class types
    //SFINAE prevents illegal code from being instantiated
    //U::* is sufficient to identify classes and structs
    //and nullptr is convertable to the method-pointer
    template<typename U>
    static std::true_type check(void(U::*)());
    
    template<typename U>
    static std::false_type check(...); //just catch anything else (variadic function)
    
    static constexpr bool value = decltype(check<T>(nullptr))::value;
};

//=================== some "classes" ===================
struct foo_struct {
};

class bar_class {
};

enum baz_enum {
};

//=================== main ===================
int main() {

    P_CYAN("press enter to continue")
    
    PNW_BOOL(is_class<foo_struct>::value)
    
    PNW_BOOL(is_class<bar_class>::value)
    
    PNW_BOOL(is_class<baz_enum>::value)
    
    PNW_BOOL(is_class<int>::value)
    
    PNW_BOOL(is_class<double>::value)
    
    PW_YELLOW("everything (static) you know about a c++ object is also known to the compiler")
    
    return 0;
}
