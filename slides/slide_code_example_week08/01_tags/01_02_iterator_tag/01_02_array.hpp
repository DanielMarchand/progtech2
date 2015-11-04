// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 08:11:03 CET
// File:    01_02_array.hpp

#ifndef _01_02_ARRAY_HEADER
#define _01_02_ARRAY_HEADER

#include "02_02_bidir_iterator.hpp"

//=================== array ===================
template <class T, uint64_t N> 
class pt2_array {
public: 
    using size_type = std::size_t;
    using value_type = T;
    using iterator = pt2_iterator<value_type>;
    
    // structors
    pt2_array() {
        for(size_type i = 0; i < size(); ++i)
            data_[0] = value_type(); // set all elements to T()
    }
    // modifying methods
    value_type & operator[](size_type const & idx) { 
        return data_[idx];
    }
    iterator begin() {
        return iterator(data_);
    }
    iterator end() {
        return iterator(data_ + N);
    }
    // const methods    
    value_type const & operator[](size_type const & idx) const {
        return data_[idx];
    }
    size_type size() const {
        return N;
    }
    
private:
    value_type data_[N];
};

#endif //_01_02_ARRAY_HEADER
