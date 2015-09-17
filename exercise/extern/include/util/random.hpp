/*******************************************************************************
 * 
 * Random Number Generator
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#ifndef UTIL_RANDOM_HEADER
#define UTIL_RANDOM_HEADER

#include <time.h>
#include <random>
#include <type_traits>

namespace util {
    namespace detail {
        using seed_type = uint64_t;

        template<typename ENGINE>
        ENGINE & get_engine(seed_type const & seed) {
            static ENGINE engine(seed);
            return engine;
        }
        template<typename ENGINE>
        seed_type & get_seed(seed_type const & init = 0) {
            static seed_type seed = init;
            return seed;
        }
        
        template<typename T, bool B>
        struct get_distr {
            using type = std::uniform_int_distribution<T>;
        };
        template<typename T>
        struct get_distr<T, false> {
            using type = std::uniform_real_distribution<T>;
        };
    }//end namespace detail
    
    template<typename ENGINE = std::mt19937>
    void seed(detail::seed_type const & seed) {
        auto & seedref = detail::get_seed<ENGINE>();
        auto & engineref = detail::get_engine<ENGINE>(seed);
        seedref = seed;
        engineref.seed(seedref);
    }
    
    template<typename ENGINE = std::mt19937>
    detail::seed_type seed() {
        return detail::get_seed<ENGINE>();
    }
    
    template<typename T, typename ENGINE = std::mt19937>
    class rng_class {
        using seed_type = detail::seed_type;
        using distr_type = typename detail::get_distr<T, std::is_integral<T>::value>::type;
    public:
        rng_class(T const & lower, T const & upper): seedref_(detail::get_seed<ENGINE>(uint64_t(time(NULL))))
                                                   , engineref_(detail::get_engine<ENGINE>(seedref_))
                                                   , distr_(lower, upper) {
        }
        T operator()() {
            return distr_(engineref_);
        }
        seed_type const & seed() noexcept {
            return seedref_;
        }
        void seed(seed_type const & seed) noexcept {
            seedref_ = seed;
            engineref_.seed(seedref_);
        }
        void set_range(T const & lower, T const & upper) {
            distr_ = distr_type(lower, upper);
        }
    private:
        seed_type & seedref_;
        ENGINE & engineref_;
        distr_type distr_;
    };
}//end namespace util
#endif //UTIL_RANDOM_HEADER
