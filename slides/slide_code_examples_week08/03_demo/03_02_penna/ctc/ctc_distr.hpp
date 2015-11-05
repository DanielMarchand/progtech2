// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    01.11.2015 13:19:14 CET
// File:    ctc_distr.hpp

#ifndef CTC_DISTR_HEADER
#define CTC_DISTR_HEADER

namespace ctc {
    template<typename T>
    struct uniform_int_distribution {
        constexpr uniform_int_distribution(T const & lower
                                         , T const & upper): lower(lower)
                                                           , upper(upper) {}
        
        template<typename ENG>
        constexpr T operator()(ENG & rng) const {
            return lower + (upper + 1 - lower) * rng.norm();
        }
        
        T lower;
        T upper;
    };
    
    template<typename T>
    struct uniform_real_distribution {
        constexpr uniform_real_distribution(T const & lower
                                          , T const & upper): lower(lower)
                                                            , upper(upper) {}
        
        template<typename ENG>
        constexpr T operator()(ENG & rng) const {
            return lower + (upper - lower) * rng.norm();
        }
        
        T lower;
        T upper;
    };
}//end namespace 

#endif //CTC_DISTR_HEADER
