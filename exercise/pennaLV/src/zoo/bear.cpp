/*******************************************************************************
 *
 * Bear Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "bear.hpp"
#include "sheep.hpp"

namespace zoo {
    // const methods
    double bear::interaction() {
        return sheep::prop.N_t / double(2 * bear::prop.N_t);
    }
    
    // static members
    const std::string bear::name = "bear";
    
}//end namespace zoo
