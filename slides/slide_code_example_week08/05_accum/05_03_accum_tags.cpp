// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 17:29:25 CET
// File:    05_03_accum_tags.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <limits>

//=================== tags ===================

namespace tag {
    struct count;
    struct mean;
    struct min;
}//end namespace 

//=================== accumulator ===================

template<typename T>
class accum_base {
public:
    accum_base & operator<<(T const &) { return (*this); };
};

template<typename T, typename tag, typename B>
class module;

//=================== count module ===================
template<typename T, typename B>
class module<T, tag::count, B>: public B {
    using super = B;
public:
    // structors
    module(): super(), count_(0) {}
    
    // modifying methods
    module & operator<<(T const & t) {
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
class module<T, tag::mean, B>: public B {
    using super = B;
public:
    // structors
    module(): super(), sum_(0) {}
    
    // modifying methods
    module & operator<<(T const & t) {
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
class module<T, tag::min, B>: public B {
    using super = B;
public:
    // structors
    module(): super(), min_(std::numeric_limits<T>::max()) {}
    
    // modifying methods
    module & operator<<(T const & t) {
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

//=================== accum_impl ===================
// variadic declaration
template<typename T, typename... Tags>
struct accum_impl;

// empty specialization
template<typename T>
struct accum_impl<T> { using type = accum_base<T>; };

// recursive specialization
template<typename T, typename Tag, typename... Rest>
struct accum_impl<T, Tag, Rest...> {
    using type = module< T, Tag, typename accum_impl<T, Rest...>::type >;
};

// less typing
template<typename T, typename... Tags>
using accum = typename accum_impl<T, Tags...>::type;

//=================== main ===================
int main() {
    P_YELLOW("basic accumulator class")
    
    accum<int, tag::min, tag::mean, tag::count> acc;
    
    CNW_NORMAL(acc << 1 << 3 << 5 << 0 << 2)
    
    CW_NORMAL(
    PNW_GREEN(acc.count())
    PNW_YELLOW(acc.mean())
    PNW_RED(acc.min())
    )
    
    return 0;
}
