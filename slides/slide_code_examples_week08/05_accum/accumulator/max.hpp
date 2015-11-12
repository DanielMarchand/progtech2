// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 14:41:15 CET
// File:    max.hpp

#ifndef MAX_HEADER
#define MAX_HEADER

#include "tag.hpp"
#include "requirement.hpp"

#include <limits> // numeric_limits

template<typename T, typename Base>
class module<T, tag::max, Base>: public Base {
    using super = Base;
public:
    // structors
    module(): super(), max_(std::numeric_limits<T>::min()) {}
    
    // modifying methods
    module & operator<<(T const & t) {
        super::operator<<(t);
        if(t > max_)
            max_ = t;
        return (*this);
    }
    void clear() {
        super::clear();
        max_ = std::numeric_limits<T>::min();
    }
    // const methods
    T const & max() const {
        return max_;
    }
    
private:
    T max_;
};

#endif //MAX_HEADER
