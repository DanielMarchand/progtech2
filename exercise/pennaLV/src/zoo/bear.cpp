/** ****************************************************************************
 * 
 * \file
 * \brief zoo::bear Implementation
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#include "bear.hpp"

// documented in zoo.hpp
namespace zoo {
    // documented in bear.hpp

    // const methods
    double bear::interaction(count_array const & N_t) {
        return N_t[tag::sheep] / double(2 * N_t[tag::bear]);
    }
    
    // static members
    const std::string bear::name = "bear";
    
}//end namespace zoo
