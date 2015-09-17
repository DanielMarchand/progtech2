/*******************************************************************************
 * 
 * Penna Simulation Code
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include "../extern/include/util/random.hpp"
#include "sheep.hpp"

#include <list>
#include <fstream>
#include <iostream>
    
int main() {
    
    // seed random number generator engine
    util::seed<>(0);
    
    // set up sheep parameters
    sheep::set_gene_size(32);
    sheep::species_repr_age = 8;
    sheep::species_threshold = 3;
    sheep::species_mut_rate = 2;
    sheep::species_N_max = 1000;
    sheep::species_N_init = 1000;
    
    // generate initial population
    std::list<sheep> pop;

    for(uint i = 0; i < sheep::species_N_init; ++i) {
        pop.push_back(sheep(sheep::random_age()));
    }
    
    // prepare output file
    std::ofstream of("./penna.txt");
    of << "time sheep" << std::endl;
    of << "#param"
       << " seed " << util::seed<>()
       << " N_init " << sheep::species_N_init
       << " N_max " << sheep::species_N_max
       << " gene_size " << sheep::species_gene_size
       << " repr_age " << sheep::species_repr_age
       << " mut_rate " << sheep::species_mut_rate
       << " threshold " << sheep::species_threshold
       << std::endl;
    
    // run simulation
    for(uint i = 0; i < 300; ++i) {
        for(std::list<sheep>::iterator it = pop.begin();  it != pop.end(); ++it) {
            auto su = not (*it).progress();
            if(su) {
                it = pop.erase(it);
                --it;
            } else {
                auto ad = it->adult();
                if(ad) {
                    pop.push_front((*it).make_child());
                }
            }
        }
        of << i << " " << sheep::species_N_t << std::endl;
    }
    of.close();
    
    // print population size
    std::cout << "sheep count " << sheep::species_N_t << std::endl;
    if(pop.size())
        std::cout << "last " << pop.back() << std::endl;

    return 0;

}
