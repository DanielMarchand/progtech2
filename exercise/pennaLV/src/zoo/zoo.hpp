// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    19.10.2015 13:27:55 CEST
// File:    zoo.hpp

#ifndef ZOO_HEADER
#define ZOO_HEADER

#include <cstdint>

namespace zoo {
    namespace tag {
        using type = uint8_t;
        
        enum zoo_enum: type {
              sheep
            , bear
            , N_animal 
        };
        
    }//end namespace 
}//end namespace 

#endif //ZOO_HEADER
