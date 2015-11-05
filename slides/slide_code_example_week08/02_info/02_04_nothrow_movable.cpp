// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 23:57:04 CET
// File:    02_04_nothrow_movable.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <type_traits> // true / false_type

//============ is T noexcept move-ctorable?  ============

template<typename T>
struct is_nothrow_move_constructible {
    // declval<U>() is just a safe way to write U()
    // since U may not have a default-ctor
    // also std::move is here for clarity, declval<U>()
    // is already an r-value
    template<typename U,
             typename S = std::enable_if_t<
                noexcept(U(std::move(std::declval<U>())))
                                          >
            >
    static std::true_type check(int);
    
    template<typename U>
    static std::false_type check(...);
    
    static constexpr bool value = decltype(check<T>(0))::value;
};

//=================== some types ===================
struct foo {
    foo(foo &&) {} // implicitly deletes the copy-ctor
    //~ foo(foo &&) noexcept {}
    
};
struct bar {
    bar(bar const &) = default;
    bar(bar &&) = delete; // implicitly deletes the copy-ctor
};
struct container {
    //~ foo f;
    //~ bar b;
};

//  +---------------------------------------------------+
//  |                   main                            |
//  +---------------------------------------------------+
int main() {
    
    PNW_BOOL(is_nothrow_move_constructible<foo>::value);
    
    PNW_BOOL(is_nothrow_move_constructible<bar>::value);
    
    PNW_BOOL(is_nothrow_move_constructible<container>::value);
    
    PNW_BOOL(is_nothrow_move_constructible<int>::value);
    
    PW_YELLOW("be aware that move silenty falls back on copy!!!");
    P_YELLOW("every copy-ctorable type is also considered move-ctorable");
    
    return 0;
}
