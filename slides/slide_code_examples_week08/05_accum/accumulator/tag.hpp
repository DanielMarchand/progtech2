// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:04:12 CET
// File:    tag.hpp

#ifndef TAG_HEADER
#define TAG_HEADER

#include <cstdint> // uint32_t

namespace tag {
    
    struct count;
    struct mean;
    struct error;
    struct min;
    struct max;
    
    template<uint32_t N>
    struct ema;
    
}//end namespace tag

#endif //TAG_HEADER
