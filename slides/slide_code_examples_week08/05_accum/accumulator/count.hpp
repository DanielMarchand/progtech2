// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:02:40 CET
// File:    count.hpp

#ifndef COUNT_HEADER
#define COUNT_HEADER

#include "tag.hpp"
#include "requirement.hpp"

template<typename T, typename Base>
class module<T, tag::count, Base>: public Base {
    using super = Base;
public:
    using count_type = uint64_t;
    
    // structors
    module(): super(), N_() {}
    
    // modifying methods
    module & operator<<(T const & t) {
        super::operator<<(t);
        ++N_;
        return (*this);
    }
    void clear() {
        super::clear();
        N_ = count_type();
    }
    // const methods
    count_type const & count() const {
        return N_;
    }
    
private:
    count_type N_;
};

#endif //COUNT_HEADER
