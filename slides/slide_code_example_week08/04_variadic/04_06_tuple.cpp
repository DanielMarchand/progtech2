// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 15:26:17 CET
// File:    04_06_tuple.cpp

//=================== include ===================
#include "../presentation.hpp"
#include <tuple>
#include <type_traits>

//=================== tuple ===================
template<typename... TN> // variadic declaration
struct tuple;

//------------------- empty tuple -------------------
template<> // empty specialization
struct tuple<> {};

//------------------- recursive pattern -------------------
// derive recursively is no performance problem if inlining is not prevented
// manually or by virtual functions. There's no single virtual function here!
template<typename T, typename... TN>// recursive specialization
struct tuple<T, TN...>: public tuple<TN...> {
    using super = tuple<TN...>;
    using value_type = T;
    
    // uref ctor
    template<typename U, typename... UN>
    tuple(U && u, UN &&... un): super(std::forward<UN>(un)...)
                              , elem(std::forward<U>(u)) {}
    
    value_type elem; // every element on each "level" has the same name
};

//------------------- get the Ith tuple-type -------------------
template<std::size_t I, typename TUP>
struct element_nr {
    using type = typename element_nr<I-1, typename TUP::super>::type;
};

template<typename TUP>
struct element_nr<0, TUP> {
    using type = TUP;
};

template<std::size_t I, typename TUP>
using element_nr_t = typename element_nr<I, TUP>::type;

//=================== get ===================
template<std::size_t I, typename TUP>
typename element_nr_t<I, TUP>::value_type & get(TUP & tup) {
    using base = element_nr_t<I, TUP>;
    return tup.base::elem;
}

//=================== make_tuple ===================
// too lazy to type
template<typename T>
using rm_ref = std::remove_reference_t<T>;

// I have to use rm_ref since T1 and T2 are part of universal 
// references (T1 && t). If called with int l-values as first argument
// T1 is int& and thus we need rm_ref...
template<typename... TN>
tuple<rm_ref<TN>...> make_tuple(TN &&... tn) {
    return tuple<rm_ref<TN>...>( std::forward<TN>(tn)... );
}

//=================== some types ===================
struct foo {
    // default ctor
    foo() = default;
    // move ctor
    foo(foo &&) = default;
};

//=================== side-note ===================
struct A {
    int x = 0;
};
struct B: public A {
    int x = 1;
};

void fct() {
    B b;
    
    PNW_BLUE(b.x)
    PNW_RED(b.A::x)
}


//=================== main ===================
int main() {
    
    fct();
    
    // since auto all "generator" functions are more convenient
    int i = 10;
    foo f;
    
    // foo is only move-ctorable!
    auto p1 =      make_tuple(i, std::move(f), 1, 1.2);
    auto p2 = std::make_tuple(i, foo(), 1, 1.2);
    
    PW_BLUE(TYPE_OF(p1))
    P_BLUE(TYPE_OF(p2))
    
    PNW_RED(    get<2>(p1))
    PN_RED(std::get<2>(p2))
         
         get<2>(p1) = 5;
    std::get<2>(p2) = 5;
    
    PNW_BLUE(    get<2>(p1))
    PN_BLUE(std::get<2>(p2))
    
    return 0;
}
