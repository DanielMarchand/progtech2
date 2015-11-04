// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 23:44:41 CET
// File:    02_03_has_method.cpp

//=================== includes ===================
#include "../presentation.hpp"

//============ trait to figure out if T::print() exists ============
template<typename T>
struct has_print_method {
    // this template takes a method pointer
    // specify the exact signature here
    template<void(T::*)(void)>
    using check_sig = int;
    
    template<typename U>
    static std::true_type check(check_sig<&U::print>); // name of method
    
    template<typename U>
    static std::false_type check(...);
    
    static constexpr bool value = decltype(check<T>(0))::value;
};

//=================== some types ===================
struct foo {
    void print() {
    }
};
struct bar {
    void print(int) {
    }
};
struct baz {
    void no_print() {
    }
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main() {
    
    PNW_BOOL(has_print_method<foo>::value);
    
    PNW_BOOL(has_print_method<bar>::value);
    
    PNW_BOOL(has_print_method<baz>::value);
    
    PW_YELLOW("every method (with exact signature) can be found");
    
    //~ PNW_BOOL(has_print_method<int>::value);
    //doesn't work because &int:: is illegal in template<void(T::*)(void)>
    //this doesn't work under sfinae...
    //one would first to check if it is a class
    //after checking for method (enable_if(is_class<...>)) see 01_03
    
    return 0;
}
