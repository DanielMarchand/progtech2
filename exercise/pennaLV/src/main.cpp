/*******************************************************************************
 *
 * PennaLV Simulation Code
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved. <- use license (discussion)
 *
 ******************************************************************************/

#include <list>
#include <fstream>
#include <iostream>

#include "zoo/bear.hpp"
#include "zoo/sheep.hpp"
#include "zoo/animal.hpp"
#include "util/random.hpp"

int main() {
    // just put everything in a namespace i.o. not to polute the global one
    using namespace zoo;
    
    // seed random number generator engine
    util::seed<>(0);

    // set up sheep parameters
    sheep::set_gene_size(32);
    sheep::prop.repr_age = 8;
    sheep::prop.threshold = 3;
    sheep::prop.mut_rate = 2;
    sheep::prop.N_max = 1000;
    sheep::prop.N_init = 1000;
    // set up bear parameters
    bear::set_gene_size(32);
    bear::prop.repr_age = 8;
    bear::prop.threshold = 3;
    bear::prop.mut_rate = 2;
    bear::prop.N_max = 1000;
    bear::prop.N_init = 1000;

    // generate initial population (can hold sheep & bear now)
    std::list<animal*> pop;

    for(uint64_t i = 0; i < sheep::prop.N_init; ++i)
        pop.push_back(new sheep(sheep::random_age()));
    
    for(uint64_t i = 0; i < bear::prop.N_init; ++i)
        pop.push_back(new bear(bear::random_age()));

    // prepare output file
    std::ofstream of("pennaLV.txt");
    of << "time sheep bear" << std::endl;
    of << "#param"
       << " seed " << util::seed<>()
       << " N_init " << sheep::prop.N_init
       << " N_max " << sheep::prop.N_max
       << " gene_size " << sheep::prop.gene_size
       << " repr_age " << sheep::prop.repr_age
       << " mut_rate " << sheep::prop.mut_rate
       << " threshold " << sheep::prop.threshold
       << " N_init_b " << bear::prop.N_init
       << " N_max_b " << bear::prop.N_max
       << " gene_size_b " << bear::prop.gene_size
       << " repr_age_b " << bear::prop.repr_age
       << " mut_rate_b " << bear::prop.mut_rate
       << " threshold_b " << bear::prop.threshold
       << std::endl;

    // run simulation
    for(uint32_t i = 0; i < 300; ++i) {
        for(auto it = pop.begin();  it != pop.end(); ++it) {
            auto * ap = (*it); // makes notation less confusing since it is
                               // a "pointer" to a pointer
            auto dead = not ap->progress();
            if(dead) {
                delete ap; // super important! otherwise memory-leak
                it = pop.erase(it);
                --it;
            } else {
                if(ap->adult()) {
                    pop.push_front(ap->make_child());
                }
            }
        }
        of << i << " " << sheep::prop.N_t << " " << bear::prop.N_t << std::endl;
    }
    of.close();

    // print population size
    std::cout << "sheep count " << sheep::prop.N_t << std::endl;
    std::cout << "bear  count " <<  bear::prop.N_t << std::endl;
    if(pop.size())
        std::cout << "last " << *pop.back() << std::endl;

    return 0;
}

