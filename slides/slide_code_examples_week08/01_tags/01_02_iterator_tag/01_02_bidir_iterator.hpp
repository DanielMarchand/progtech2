// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 08:19:12 CET
// File:    01_02_bidir_iterator.hpp

#ifndef _01_02_BIDIR_ITERATOR_HEADER
#define _01_02_BIDIR_ITERATOR_HEADER

#include <iterator>

#include "../../presentation.hpp"

//=================== iterator ===================
template<typename T>
class pt2_iterator {
public:
    using value_type = T;
    
    // structors
    pt2_iterator(T * t): ptr_(t) {};
    
    // modifying methods
    pt2_iterator& operator++() { 
        PW_GREEN("++it")
        ++ptr_;
        return (*this);
    }
    pt2_iterator& operator--() {
        PW_RED("--it")
        --ptr_;
        return (*this);
    }
    //~ pt2_iterator & operator+=(int const & dist) {
        //~ PW_YELLOW("it += " + std::to_string(dist));
        //~ ptr_ += dist;
        //~ return (*this);
    //~ }
    
    // const methods
    value_type & operator*  () const { return *ptr_; }
    value_type * operator-> () const { return  ptr_; }
    bool operator== ( const pt2_iterator& rhs ) const { return ptr_ == rhs.ptr_; }
    bool operator!= ( const pt2_iterator& rhs ) const { return ptr_ != rhs.ptr_; }

private:
    value_type * ptr_;
};

namespace std {
    template<typename T>
    struct iterator_traits<pt2_iterator<T>> {
        using difference_type = int64_t;
        //~ using iterator_category = std::random_access_iterator_tag;
        using iterator_category = std::bidirectional_iterator_tag;
    };
    
    
}//end namespace std

#endif //_02_02_BIDIR_ITERATOR_HEADER
