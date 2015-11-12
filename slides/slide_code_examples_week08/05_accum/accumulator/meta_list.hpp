// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:02:46 CET
// File:    meta_list.hpp

#ifndef META_LIST_HEADER
#define META_LIST_HEADER

//=================== meta list ===================
template<typename T, typename N>
struct listnode {
    using type = T;
    using next = N;
};

struct listend;

//=================== make_list ===================
template<typename... D> // variadic version
struct make_list_impl;

template<> // empty list
struct make_list_impl<> {
    using type = listend;
};

template<typename T, typename... D> // recursive version
struct make_list_impl<T, D...> {
    using type = listnode<T, typename make_list_impl<D...>::type>;
};

template<typename... T> // only for less typing
using make_list = typename make_list_impl<T...>::type;

//=================== concatenate lists ===================
template<typename L1, typename... Rest>
struct concat_list_impl {
    using type = listnode< typename L1::type
                         , typename concat_list_impl< typename L1::next
                                                    , Rest...
                                                    >::type
                         >;
};

template<typename... Rest>
struct concat_list_impl<listend, Rest...> {
    using type = typename concat_list_impl<Rest...>::type;
};

template<typename Last>
struct concat_list_impl<listend, Last> {
    using type = Last;
};

template<typename... L>
using concat_list = typename concat_list_impl<L...>::type;

//=================== remove a type from a list ===================
template<typename L, typename Rm, typename... Res>
struct remove_from_impl {
    using type = typename remove_from_impl< typename L::next
                                          , Rm
                                          , Res...
                                          , typename L::type
                                          >::type;
};

template<typename N, typename Rm, typename... Res>
struct remove_from_impl<listnode<Rm, N>, Rm, Res...> {
    using type = typename remove_from_impl< N
                                          , Rm
                                          , Res...
                                          // dont add T
                                          >::type;
};

template<typename Rm, typename... Res>
struct remove_from_impl<listend, Rm, Res...> {
    using type = make_list<Res...>;
};

template<typename L, typename Rm>
using remove_from = typename remove_from_impl< L, Rm>::type;

//=================== make list unique ===================
template<typename L, typename... Res>
struct unique_list_impl {
    using type = typename unique_list_impl< remove_from< typename L::next
                                                       , typename L::type
                                                       >
                                          , Res...
                                          , typename L::type
                                          >::type;
};

template<typename... Res>
struct unique_list_impl<listend, Res...> {
    using type = make_list<Res...>;
};

template<typename L>
using unique_list = typename unique_list_impl<L>::type;

//=================== invert list ===================
template<typename N, typename... D>
struct invert_list_impl {
    using type = typename invert_list_impl< typename N::next
                                          , typename N::type
                                          , D...
                                          >::type;
};

template<typename... D>
struct invert_list_impl<listend, D...> {
    using type = make_list<D...>;
};

template<typename L>
using invert_list = typename invert_list_impl< typename L::next
                                             , typename L::type
                                             >::type;

#endif //META_LIST_HEADER
