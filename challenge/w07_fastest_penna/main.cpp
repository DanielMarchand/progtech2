// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:30:45 CET
// File:    main.cpp

#include <iostream>
//~ #include "sim.hpp"
//~ #include "list_sim.hpp"
//~ #include "vec_slow_sim.hpp"
#include "vec_sim.hpp"
    
int main() {
    sim::pennaLV( 0     // seed
                , "pennaLV.txt" // filename
                , 300   // N_generation
                , 32    // sheep_gene_size
                , 8     // sheep_repr_age
                , 3     // sheep_threshold
                , 2     // sheep_mut_rate
                , 1000  // sheep_N_init
                , 1000  // sheep_N_max
                , 32    // bear_gene_size
                , 8     // bear_repr_age
                , 3     // bear_threshold
                , 2     // bear_mut_rate
                , 1000  // bear_N_init
                , 1000  // bear_N_max
                );
    return 0;
}
