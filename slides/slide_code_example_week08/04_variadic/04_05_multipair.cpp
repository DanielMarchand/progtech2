// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 16:23:29 CET
// File:    04_05_multipair.cpp

//=================== include ===================
#include "../presentation.hpp"
#include <tuple>
#include <type_traits>

//=================== pair ===================
struct empty_pair {
};

template<typename T1>
struct first_pair: public empty_pair {
    using super = empty_pair;
    using first_type = T1;
    
    // ctor that takes univesal references
    template<typename U1>
    first_pair(U1 && u1): super()
                        , first(std::forward<U1>(u1))
    {}
    
    first_type first;
};

template<typename T1, typename T2>
struct second_pair: public first_pair<T1> {
    using super = first_pair<T1>;
    using second_type = T2;
    // ctor that takes univesal references
    template<typename U1, typename U2>
    second_pair(U1 && u1, U2 && u2): super(std::forward<U1>(u1))
                                   , second(std::forward<U2>(u2)) 
    {}
    
    second_type second;
};

template<typename T1, typename T2, typename T3>
struct third_pair: public second_pair<T1, T2> {
    using super = second_pair<T1, T2>;
    using third_type = T3;
    // ctor that takes univesal references
    template<typename U1, typename U2, typename U3>
    third_pair(U1 && u1, U2 && u2, U3 && u3): super(std::forward<U1>(u1)
                                                  , std::forward<U2>(u2))
                                            , third(std::forward<U3>(u3)) 
    {}
    
    third_type third;
};

//=================== make_pair ===================
// too lazy to type
template<typename T>
using rm_ref = std::remove_reference_t<T>;

// I have to use rm_ref since T1 and T2 are part of universal 
// references (T1 && t). If called with int l-values as first argument
// T1 is int& and thus we need rm_ref...
template<typename T1>
first_pair<rm_ref<T1>> make_1pair(T1 && t1) {
    return first_pair< rm_ref<T1> >( std::forward<T1>(t1));
}
template<typename T1, typename T2>
second_pair<rm_ref<T1>, rm_ref<T2>> make_2pair(T1 && t1, T2 && t2) {
    return second_pair< rm_ref<T1>, rm_ref<T2> >( std::forward<T1>(t1)
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
    auto p1 = make_1pair(i);
    auto p2 = make_2pair(i, foo());
    third_pair<int, int, int> p3(1, 2, 3);
    
    P_BLUE(TYPE_OF(p1))
    P_BLUE(TYPE_OF(p2))
    P_BLUE(TYPE_OF(p3))
    
    return 0;
}
