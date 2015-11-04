// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:37:48 CET
// File:    global.hpp

#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER

#include <array>

namespace opt {
    
    
    using age_type = uint32_t;
    using mut_type = uint32_t;
    using cnt_type = uint64_t;
    constexpr cnt_type max_gene = 32;
    using count_array = std::array<cnt_type, 2>;
    enum asta: age_type {
          dead = age_type(100)
        , newborn = age_type(200)
    };

}//end namespace 

#endif //GLOBAL_HEADER
