// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 14:09:45 CET
// File:    error.hpp

#ifndef ERROR_HEADER
#define ERROR_HEADER

#include "tag.hpp"
#include "requirement.hpp"

#include <cmath>       // sqrt
#include <type_traits> // declval

namespace detail {
    template<>
    struct requirement<tag::error> {
        using type = make_list<tag::mean>;
    };
}//end namespace detail

template<typename T, typename Base>
class module<T, tag::error, Base>: public Base {
    using super = Base;
public:
    using mean_type = typename super::mean_type;
    using error_type = decltype(sqrt(std::declval<mean_type>() / double()));
    // structors
    module(): super(), sum2_() {}
    
    // modifying methods
    module & operator<<(T const & t) {
        super::operator<<(t);
        sum2_ += error_type(t) * t;
        return (*this);
    }
    void clear() {
        super::clear();
        sum2_ = T();
    }
    // const methods
    error_type std() const {
        return sqrt((sum2_ - super::mean() * super::mean() * super::count()) 
                  / (super::count() - 1));
    }
    
private:
    error_type sum2_;
};

#endif //ERROR_HEADER
