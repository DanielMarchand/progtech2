/*******************************************************************************
 *
 * Bear Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef BEAR_HEADER
#define BEAR_HEADER

#include <string>

#include "animal_crtp.hpp"

namespace zoo {

    class bear: public animal_crtp<bear> {
        using super = animal_crtp<bear>;
        
        public:
        // structors & assignment
        bear(age_type const & age = 0): super(age) {
        }
        bear(bear const & rhs): super(rhs) {
        }
        static double interaction();
        
        public:
        static const std::string name;
    };
    
}//end namespace zoo

#endif //BEAR_HEADER
