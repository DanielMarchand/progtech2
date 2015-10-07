/*******************************************************************************
 *
 * Sheep Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "bear.hpp"
#include "sheep.hpp"

namespace zoo {
    // const methods
    double sheep::interaction() {
        return 1 - 0.1 * bear::prop.N_t / double(sheep::prop.N_t);
    }
    
    // static members
    const std::string sheep::name = "sheep";
}//end namespace zoo

