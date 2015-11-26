/** ****************************************************************************
 * 
 * \file
 * \brief zoo::sheep Implementation
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#include "sheep.hpp"

// documented in zoo.hpp
namespace zoo {
    // documented in sheep.hpp

    // const methods
    double sheep::interaction(count_array const & N_t) {
        return 1 - 0.1 * N_t[tag::bear] / double(N_t[tag::sheep]);
    }
    
    // static members
    const std::string sheep::name = "sheep";
    
}//end namespace zoo

