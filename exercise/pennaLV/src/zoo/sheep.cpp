/*******************************************************************************
 *
 * Sheep Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "sheep.hpp"

namespace zoo {
    // const methods
    double sheep::interaction(sim::count_array const & N_t) {
        return 1 - 0.1 * N_t[tag::bear] / double(N_t[tag::sheep]);
    }
    
    // static members
    const std::string sheep::name = "sheep";
    
}//end namespace zoo

