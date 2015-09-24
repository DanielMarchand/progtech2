/*******************************************************************************
 *
 * Penna Simulation Code
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved. <- use license (discussion)
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
    sheep::prop.repr_age = 8;
    sheep::prop.threshold = 3;
    sheep::prop.mut_rate = 2;
    sheep::prop.N_max = 1000;
    sheep::prop.N_init = 1000;

    // generate initial population
    std::list<sheep> pop;

    for(uint i = 0; i < sheep::prop.N_init; ++i) {
        pop.push_back(sheep(sheep::random_age()));
    }

    // prepare output file
    std::ofstream of("penna.txt");
    of << "time sheep" << std::endl;
    of << "#param"
       << " seed " << util::seed<>()
       << " N_init " << sheep::prop.N_init
       << " N_max " << sheep::prop.N_max
       << " gene_size " << sheep::prop.gene_size
       << " repr_age " << sheep::prop.repr_age
       << " mut_rate " << sheep::prop.mut_rate
       << " threshold " << sheep::prop.threshold
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
        of << i << " " << sheep::prop.N_t << std::endl;
    }
    of.close();

    // print population size
    std::cout << "sheep count " << sheep::prop.N_t << std::endl;
    if(pop.size())
        std::cout << "last " << pop.back() << std::endl;

    return 0;
}
