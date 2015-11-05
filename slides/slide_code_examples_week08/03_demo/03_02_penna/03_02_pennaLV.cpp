// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:30:45 CET
// File:    main.cpp

#include <iostream>
#include "vec_sim.hpp"

//=================== main =================== 
int main() {
    // run the entire pennaLV simulation during compiletime!
    auto constexpr res 
    = sim::pennaLV< 1000  // sheep_N_max
                  , 1000  // bear_N_max
                  , 10    // N_generation
                  >(0     // seed
                  , 32    // sheep_gene_size
                  , 8     // sheep_repr_age
                  , 3     // sheep_threshold
                  , 2     // sheep_mut_rate
                  , 1000  // sheep_N_init
                  , 32    // bear_gene_size
                  , 8     // bear_repr_age
                  , 3     // bear_threshold
                  , 2     // bear_mut_rate
                  , 1000  // bear_N_init
                  );
    
    for(uint i = 0; i < res.size(); ++i)
        std::cout << res[i].first << " " << res[i].second << std::endl;
    
    return 0;
}
