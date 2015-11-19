/** ****************************************************************************
 * 
 * \file
 * \brief Main program
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright For free use, no rights reserved, with no warranty whatsoever.
 * \details Demonstration for usage of simulation and animal libraries.
 * \cond IMPLEMENTATION_DETAIL_DOC
 * 
 ******************************************************************************/

//~ #include <util/profiler.hpp>

#include <simulation.hpp>
#include <zoo/bear.hpp>
#include <zoo/sheep.hpp>
#include <zoo/adapter.hpp>

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
    
    std::map<std::string, std::string> param;
    
    param["seed"] = std::to_string(util::seed<>());
    
    param["N_init_sheep"] = std::to_string(N_init[sheep::name]);
    param["N_max_sheep"] = std::to_string(N_max[sheep::name]);
    param["gene_size_sheep"] = std::to_string(sheep::prop.gene_size);
    param["repr_age_sheep"] = std::to_string(sheep::prop.repr_age);
    param["mut_rate_sheep"] = std::to_string(sheep::prop.mut_rate);
    param["threshold"] = std::to_string(sheep::prop.threshold);
    
    param["N_init_sheep"] = std::to_string(N_init[sheep::name]);
    param["N_max_sheep"] = std::to_string(N_max[sheep::name]);
    param["gene_size_sheep"] = std::to_string(sheep::prop.gene_size);
    param["repr_age_sheep"] = std::to_string(sheep::prop.repr_age);
    param["mut_rate_sheep"] = std::to_string(sheep::prop.mut_rate);
    param["threshold"] = std::to_string(sheep::prop.threshold);
    
    //~ MIB_START("main")
    //~ MIB_START("ctor")
    
    // we had to change the order of sheep and bear
    sim::simulation<zoo_to_sim<bear>, zoo_to_sim<sheep>> pennaLV("pennaLV.txt"
                                                                 , param
                                                                 , N_max
                                                                 , N_init);
    
    //~ MIB_NEXT("run")
    pennaLV.run(300);
    //~ MIB_NEXT("print")
    pennaLV.print();
    
    //~ MIB_STOP("print")
    //~ MIB_STOP("main")
    
    //~ MIB_PRINT("cycle")
    //~ MIB_SAVE("cycle", "pennaLV_variadic.txt")
    
    return 0;
}
