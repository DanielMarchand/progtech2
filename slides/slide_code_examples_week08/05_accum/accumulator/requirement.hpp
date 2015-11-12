// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:22:24 CET
// File:    requirement.hpp

#ifndef REQUIREMENT_HEADER
#define REQUIREMENT_HEADER

#include "meta_list.hpp"

namespace detail {
    
    template<typename Tag>
    struct requirement {
        using type = make_list<>;
    };
    
    /*
    RQ(tag)->list             # requirement
    RR(L) -> list             # resolve requirement
    
    RR(L):
        res = []
        for t in L:
            res += RS(RQ(t))  # concat< resolve_impl < requirement <t> > >
            res += [t]        # make_list<t>
        return res
    */
    template<typename L, typename Res = listend>
    struct resolve_impl {
        using type = typename resolve_impl< typename L::next
                                          , concat_list< 
                                                Res
                                              , typename resolve_impl<
                                                  typename requirement<
                                                      typename L::type
                                                  >::type
                                                >::type 
                                              , make_list<typename L::type>
                                            >
                                          >::type;
    };
    
    template<typename Res>
    struct resolve_impl<listend, Res> {
        using type = Res;
    };
    
    template<typename L>
    using resolve_requirement = typename resolve_impl<L>::type;
    
}//end namespace detail

template<typename T, typename Tag, typename Base>
class module;

#endif //REQUIREMENT_HEADER
