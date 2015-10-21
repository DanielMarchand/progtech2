// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    05.09.2015 20:16:09 CEST
// File:    accumulator.hpp

#ifndef UTIL_ACCUMULATOR_HEADER
#define UTIL_ACCUMULATOR_HEADER

#include <cmath>
#include <iomanip>
#include <iostream>

namespace util {
    template<typename T>
    class accumulator {
        using mean_type = decltype((T() + T()) / double());
        using count_type = uint64_t;
    public:
        //------------------- structors -------------------
        accumulator(): n_(), sum_(), sum2_() {}
        //------------------- methods -------------------
        inline void operator<<(T const & val) {
            ++n_;
            sum_ += val;
            sum2_ += val * val;
        }
        inline void clear() {
            n_ = 0;
            sum_ = 0;
            sum2_ = 0;
        }
        //-------------------const methods -------------------
        inline mean_type mean() const {
            return mean_type(sum_) / n_;
        }
        inline mean_type dev() const {
            mean_type sc0 = n_ - 1;
            return sqrt(sum2_ / sc0 - sum_ * sum_ / sc0 / n_);
        }
        inline mean_type std() const {
            using std::sqrt;
            return dev() / sqrt(n_);
        }
        inline count_type const & count() const {
            return n_;
        }
        inline T const & sum() const {
            return sum_;
        }
    private:
        count_type n_;
        T sum_;
        T sum2_;
    };

    template<typename T>
    inline std::ostream & operator<<(std::ostream & os, accumulator<T> const & acc) {
        std::streamsize p = os.precision();
        os << acc.mean() << " +/- " << std::setprecision(3) << (100 * acc.std() / acc.mean()) << "% (n = " << acc.count() << ")";
        os.precision(p);
        return os;
    }
}//end namespace util

#endif //UTIL_ACCUMULATOR_HEADER
