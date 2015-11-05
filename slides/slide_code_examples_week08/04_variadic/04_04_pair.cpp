// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 14:42:04 CET
// File:    04_04_pair.cpp

//=================== include ===================
#include "../presentation.hpp"
#include <utility>
#include <type_traits>

//=================== pair ===================
template<typename T1, typename T2>
struct pair {
    // ctor that takes univesal references
    template<typename U1, typename U2>
    pair(U1 && u1, U2 && u2): first(std::forward<U1>(u1))
                            , second(std::forward<U2>(u2)) {}
    
    // data
    T1 first;
    T2 second;
};

//=================== make_pair ===================
// too lazy to type
template<typename T>
using rm_ref = std::remove_reference_t<T>;

// I have to use rm_ref since T1 and T2 are part of universal 
// references (T1 && t). If called with int l-values as first argument
// T1 is int& and thus we need rm_ref...
template<typename T1, typename T2>
pair<rm_ref<T1>, rm_ref<T2>> make_pair(T1 && t1, T2 && t2) {
    //~ CW_NORMAL(
    //~ PN_BLUE(TYPE(T1))
    //~ PN_BLUE(TYPE(rm_ref<T1>))
    //~ PNW_BLUE(TYPE(T2))
    //~ PN_BLUE(TYPE(rm_ref<T2>))
    //~ )
    return pair< rm_ref<T1>, rm_ref<T2> >( std::forward<T1>(t1)
                                         , std::forward<T2>(t2));
}

//=================== some types ===================
struct foo {
    // default ctor
    foo() = default;
    // move ctor
    foo(foo &&) = default;
};

//=================== main ===================
int main() {
    
    // since auto all "generator" functions are more convenient
    int i = 10;
    foo f;
    
    // foo is only move-ctorable!
    auto p1 =      make_pair(i, std::move(f));
    auto p2 = std::make_pair(i, foo());
    
    PW_BLUE(TYPE_OF(p1))
    P_BLUE(TYPE_OF(p2))
    
    return 0;
}
