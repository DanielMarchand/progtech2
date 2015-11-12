/*******************************************************************************
 *
 * Bear Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "bear.hpp"

namespace zoo {
    // const methods
    double bear::interaction(count_array const & N_t) {
        return N_t[tag::sheep] / double(2 * N_t[tag::bear]);
    }
    
    // static members
    const std::string bear::name = "bear";
    
}//end namespace zoo
