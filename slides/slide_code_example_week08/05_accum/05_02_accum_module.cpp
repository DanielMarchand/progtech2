// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 17:29:44 CET
// File:    05_02_accum_module.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <limits>
//=================== accumulator ===================

template<typename T>
class accum_base {
public:
    accum_base & operator<<(T const &) { return (*this); };
};

//=================== count module ===================
template<typename T, typename B>
class count_module: public B {
    using super = B;
public:
    // structors
    count_module(): super(), count_(0) {}
    
    // modifying methods
    count_module & operator<<(T const & t) {
        super::operator<<(t);
        ++count_;
        return (*this);
    }
    // const methods
    uint64_t const & count() const {
        return count_;
    }
private:
    uint64_t count_;
};

//=================== mean module ===================
template<typename T, typename B>
class mean_module: public B {
    using super = B;
public:
    // structors
    mean_module(): super(), sum_(0) {}
    
    // modifying methods
    mean_module & operator<<(T const & t) {
        super::operator<<(t);
        sum_ += t;
        return (*this);
    }
    // const methods
    decltype(std::declval<T>()/double()) mean() const {
        return sum_ / double(super::count());
    }
private:
    T sum_;
};

//=================== min module ===================
template<typename T, typename B>
class min_module: public B {
    using super = B;
public:
    // structors
    min_module(): super(), min_(std::numeric_limits<T>::max()) {}
    
    // modifying methods
    min_module & operator<<(T const & t) {
        super::operator<<(t);
        if(t < min_)
            min_ = t;
        return (*this);
    }
    // const methods
    T const & min() const {
        return min_;
    }
private:
    T min_;
};


template<typename T>
using accum = min_module<T, mean_module<T, count_module<T, accum_base<T>>>>;

template<typename T>
using only_count_accum = count_module<T, accum_base<T>>;

template<typename T>
using only_min_accum = min_module<T, accum_base<T>>;

template<typename T>
using only_mean_accum = mean_module<T, accum_base<T>>;

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
    
    mean_module<int, accum_base<int>> acc2;
    acc2 << 1;
    //~ acc2.mean(); // here we have a problem since we forgot 
                 //~ // to derive form count_module
    
    return 0;
}
