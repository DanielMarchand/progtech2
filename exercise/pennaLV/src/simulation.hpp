/*******************************************************************************
 *
 * Simulation Class Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef SIMULATION_HEADER
#define SIMULATION_HEADER

#include <zoo/animal.hpp>
#include <sim_typedef.hpp>

#include <map>
#include <list>
#include <fstream>

namespace sim {
    class simulation {
    public:
        
        // structors
        simulation( std::string const & file
                  , uint64_t const & seed
                  , std::map<std::string, uint64_t> const & N_max
                  , std::map<std::string, uint64_t> const & N_init
                  );
        // modifying methods
        void run(uint32_t const & N_generation);
        // const methods
        inline count_array const & N_t() const {
            return N_t_;
        }
        void print() const;
    private:
        std::ofstream of_;
        std::list<std::shared_ptr<zoo::animal>> pop_;
        count_array N_max_;
        count_array N_init_;
        count_array N_t_;
    };
}//end namespace sim

#endif //SIMULATION_HEADER
