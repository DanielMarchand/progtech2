// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 16:38:51 CET
// File:    05_01_accum_begin.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <limits>

//=================== accumulator ===================

template<typename T>
class accum {
public:
    // structors
    accum(): count_(0)
           , sum_()
           , min_(std::numeric_limits<T>::max()) 
    {}
    // modifying methods
    accum & operator<<(T const & t) {
        ++count_;
        sum_ += t;
        if(t < min_)
            min_ = t;
        return (*this);
    }
    // const methods
    uint64_t const & count() const {
        return count_;
    }
    
    decltype(std::declval<T>()/double()) mean() const {
        return sum_ / double(count());
    }
    
    T const & min() const {
        return min_;
    }
private:
    uint64_t count_;
    T sum_;
    T min_;
};



//=================== main ===================
int main() {
    P_YELLOW("basic accumulator class")
    
    accum<int> acc;
    
    CNW_NORMAL(acc << 1 << 3 << 5 << 0 << 2)
    
    CW_NORMAL(
    PNW_GREEN(acc.count())
    PNW_YELLOW(acc.mean())
    PNW_RED(acc.min())
    )
    
    return 0;
}
