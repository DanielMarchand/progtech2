// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:02:44 CET
// File:    mean.hpp

#ifndef MEAN_HEADER
#define MEAN_HEADER

#include "tag.hpp"
#include "requirement.hpp"

#include <type_traits> // declval

namespace detail {
    template<>
    struct requirement<tag::mean> {
        using type = make_list<tag::count>;
    };
}//end namespace detail

template<typename T, typename Base>
class module<T, tag::mean, Base>: public Base {
    using super = Base;
public:
    using mean_type = decltype(std::declval<T>() / double());
    // structors
    module(): super(), sum_() {}
    
    // modifying methods
    module & operator<<(T const & t) {
        super::operator<<(t);
        sum_ += t;
        return (*this);
    }
    void clear() {
        super::clear();
        sum_ = T();
    }
    // const methods
    mean_type mean() const {
        return sum_ / super::count();
    }
    
private:
    mean_type sum_;
};

#endif //MEAN_HEADER
