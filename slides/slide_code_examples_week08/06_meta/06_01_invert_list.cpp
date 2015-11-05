// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 21:12:26 CET
// File:    06_01_invert_list.cpp

//=================== includes ===================
#include "../presentation.hpp"

//=================== meta list ===================
template<typename T, typename N>
struct node {
    using type = T;
    using next = N;
};

// marks the end of the list
struct endnode;

//=================== make_list ===================
template<typename... D> // variadic declaration
struct make_list_impl;

template<> // empty specialization
struct make_list_impl<> {
    using type = endnode;
};

template<typename T, typename... Rest> // recursive specialization
struct make_list_impl<T, Rest...> {
    using type = node<T, typename make_list_impl<Rest...>::type>;
};

// only for less typing
template<typename... T>
using make_list = typename make_list_impl<T...>::type;

//=================== concat two list ===================
template<typename L, typename L2>
struct concat_list_impl {
    using type = node< typename L::type
                     , typename concat_list_impl< typename L::next
                                                , L2
                                                >::type
                     >;
};
// if the end of the first list is reached
template<typename L2>
struct concat_list_impl<endnode, L2> {
    using type = L2;
};

// for less typing
template<typename L1, typename L2>
using concat_list = typename concat_list_impl<L1, L2>::type;

//=================== main ===================
int main() {
    
    // create a meta-list with {int, float}
    using m1 = node<int, node<float, endnode>>;
    
    PNWW_RED(TYPE(m1))
    
    // easier way to make a list
    using l1 = make_list<int, float>;
    
    PNWW_BLUE(TYPE(l1))
    
    using l2 = make_list<bool, char>;
    
    // join two list
    using l3 = concat_list<l1, l2>;
    
    PNWW_BLUE(TYPE(l2))
    PNWW_BLUE(TYPE(l3))
    
    return 0;
}
