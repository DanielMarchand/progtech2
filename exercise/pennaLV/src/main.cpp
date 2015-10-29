// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    19.10.2015 10:44:57 CEST
// File:    new_main.cpp


//~ #include <util/profiler.hpp>

#include <simulation.hpp>
#include <zoo/bear.hpp>
#include <zoo/sheep.hpp>

#include <map>
#include <iostream>

int main() {
    // just put everything in a namespace i.o. not to pollute the global one
    using namespace zoo;
    
    // seed random number generator engine
    util::seed<>(0);
    
    std::map<std::string, uint64_t> N_init;
    std::map<std::string, uint64_t> N_max;
    // set up sheep parameters
    sheep::set_gene_size(32);
    sheep::prop.repr_age = 8;
    sheep::prop.threshold = 3;
    sheep::prop.mut_rate = 2;
    N_init[sheep::name] = 1000;
    N_max[sheep::name] = 1000;
    
    // set up bear parameters
    bear::set_gene_size(32);
    bear::prop.repr_age = 8;
    bear::prop.threshold = 3;
    bear::prop.mut_rate = 2;
    N_init[bear::name] = 1000;
    N_max[bear::name] = 1000;
    
    //~ MIB_START("main")
    //~ MIB_START("ctor")

    sim::simulation<sheep, bear> pennaLV("pennaLV.txt"
                                        , util::seed<>()
                                        , N_max
                                        , N_init);
    
    //~ MIB_NEXT("run")
    pennaLV.run(300);
    //~ MIB_NEXT("print")
    pennaLV.print();
    
    //~ MIB_STOP("print")
    //~ MIB_STOP("main")
    
    //~ MIB_PRINT("cycle")
    //~ MIB_SAVE("cycle", "pennaLV_cycle.txt")
    
    return 0;
}
