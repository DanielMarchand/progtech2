// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    31.08.2015 17:12:23 CEST
// File:    random.hpp

#ifndef CTC_RANDOM_HEADER
#define CTC_RANDOM_HEADER

#include "ctc_mersenne.hpp"
#include "ctc_distr.hpp"
#include <type_traits>

namespace ctc {
    namespace detail {
        using seed_type = uint64_t;
        
        template<typename T, bool B>
        struct get_distr {
            using type = ctc::uniform_int_distribution<T>;
        };
        template<typename T>
        struct get_distr<T, false> {
            using type = ctc::uniform_real_distribution<T>;
        };
    }//end namespace detail
    
    
    template<typename T, typename ENGINE = ctc::mt19937>
    class rng_class {
        using seed_type = detail::seed_type;
        using distr_type = typename detail::get_distr<T, std::is_integral<T>::value>::type;
    public:
        constexpr rng_class(T const & lower
                          , T const & upper
                          , ENGINE & engineref):  engineref_(engineref)
                                                , distr_(lower, upper) {
        }
        constexpr T operator()() {
            return distr_(engineref_);
        }
        constexpr void set_range(T const & lower, T const & upper) {
            distr_ = distr_type(lower, upper);
        }
    private:
        ENGINE & engineref_;
        distr_type distr_;
    };
}//end namespace ctc
#endif //CTC_RANDOM_HEADER
