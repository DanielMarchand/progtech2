// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 14:41:15 CET
// File:    min.hpp

#ifndef MIN_HEADER
#define MIN_HEADER

#include "tag.hpp"
#include "requirement.hpp"

#include <limits> // numeric_limits

template<typename T, typename Base>
class module<T, tag::min, Base>: public Base {
    using super = Base;
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
    void clear() {
        super::clear();
        min_ = std::numeric_limits<T>::max();
    }
    // const methods
    T const & min() const {
        return min_;
    }
    
private:
    T min_;
};

#endif //MIN_HEADER
