// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:02:35 CET
// File:    accum.hpp

#ifndef ACCUM_HEADER
#define ACCUM_HEADER

#include "tag.hpp"
#include "count.hpp"
#include "mean.hpp"
#include "error.hpp"
#include "min.hpp"
#include "max.hpp"
#include "ema.hpp"
#include "accum_base.hpp"


template<typename... T>
struct pass {};

template<typename T, typename L>
struct deriver_impl {
    using type = module< T
                       , typename L::type
                       , typename deriver_impl<T, typename L::next>::type
                       >;
};
template<typename T>
struct deriver_impl<T, listend> {
    using type = accum_base<T>;
};

template<typename T, typename L>
using deriver = typename deriver_impl<T, L>::type;

template<typename T, typename... Tags>
using accum  = deriver< T
                      , invert_list<
                            unique_list<
                                detail::resolve_requirement<
                                    make_list<Tags...>
                                           >
                                       >
                                   >
                      >;

#endif //ACCUM_HEADER
