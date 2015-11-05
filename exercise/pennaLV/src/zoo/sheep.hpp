/*******************************************************************************
 *
 * Sheep Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef SHEEP_HEADER
#define SHEEP_HEADER

#include <string>

#include <sim_typedef.hpp>
#include "zoo.hpp"
#include "animal_crtp.hpp"

namespace zoo {

    class sheep: public animal_crtp<sheep> {
        using super = animal_crtp<sheep>;
        
        public:
        // structors & assignment
        inline sheep(age_type const & age = 0): super(age) {
        }
        inline sheep(sheep const & rhs): super(rhs) {
        }
        static double interaction(sim::count_array const & N_t);
        
        public:
        static const std::string name;
        static const tag::animal_enum index = tag::sheep;
    };
    
}//end namespace zoo

#endif //SHEEP_HEADER
