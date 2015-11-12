/*******************************************************************************
 * 
 * enum and types used by the thunder-structs
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER

namespace dir {
    using type = int;
    enum: type { up_left
               , left
               , down_left
               , down_right
               , right
               , up_right
               , N
               };
}//end namespace dir

struct field_type {
    int cnt;
    int player;
};


#endif //GLOBAL_HEADER
