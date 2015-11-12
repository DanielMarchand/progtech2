// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 15:01:47 CET
// File:    ema.hpp

#ifndef EMA_HEADER
#define EMA_HEADER

#include "tag.hpp"
#include "requirement.hpp"

#include <type_traits> // declval

template<typename T, typename Base, uint32_t N>
class module<T, tag::ema<N>, Base>: public Base {
    using super = Base;
public:
    using ema_type = decltype(std::declval<T>() / double());
    // structors
    module(): super(), ema_() {}
    
    // modifying methods
    module & operator<<(T const & t) {
        super::operator<<(t);
        ema_ = ((N-1) * (ema_)) / N + t;
        return (*this);
    }
    void clear() {
        super::clear();
        ema_ = T();
    }
    // const methods
    ema_type ema() const {
        return ema_ / N;
    }
    
private:
    ema_type ema_;
};

#endif //EMA_HEADER
