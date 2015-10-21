// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    19.10.2015 11:35:03 CEST
// File:    simulation_typedef.hpp

#ifndef SIMULATION_TYPEDEF_HEADER
#define SIMULATION_TYPEDEF_HEADER

#include <array>
#include <zoo/zoo.hpp>

namespace sim {
    using count_type = uint64_t;
    using count_array = std::array<count_type, zoo::tag::N_animal>;
}//end namespace 

#endif //SIMULATION_TYPEDEF_HEADER
