/*******************************************************************************
 * 
 * \file
 * \brief Type List Helper
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright For free use, no rights reserved, with no warranty whatsoever.
 * \cond IMPLEMENTATION_DETAIL_DOC
 * 
 ******************************************************************************/

#ifndef MTP_TYPE_LIST_HEADER
#define MTP_TYPE_LIST_HEADER

namespace mtp {
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

    //=================== reverse list ===================
    template<typename N, typename... D>
    struct reverse_list_impl {
        using type = typename reverse_list_impl<typename N::next, typename N::type, D...>::type;
    };

    template<typename... D>
    struct reverse_list_impl<endnode, D...> {
        using type = make_list<D...>;
    };

    template<typename L>
    using reverse_list = typename reverse_list_impl<typename L::next, typename L::type>::type;

    //=================== meta_infuse list into variadic template ===================
    template<template<typename...> class V, typename L, typename... D>
    struct infuse_list_impl {
        // by changing D..., L::type to L::type, D... we could reverse while infusing
        using type = typename infuse_list_impl<V, typename L::next, D..., typename L::type>::type;
    };
    
    template<template<typename...> class V, typename... D>
    struct infuse_list_impl<V, endnode, D...> {
        using type = V<D...>; // call the actual variadic template
    };

    template<template<typename...> class V, typename L>
    using infuse_list = typename infuse_list_impl<V, typename L::next, typename L::type>::type;

}//end namespace mtp

#endif //MTP_TYPE_LIST_HEADER
