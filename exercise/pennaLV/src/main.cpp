/** ****************************************************************************
 * 
 * \file
 * \brief Main program
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * \details Demonstration for usage of simulation and animal libraries.
 * \cond IMPLEMENTATION_DETAIL_DOC
 * 
 ******************************************************************************/

#include <sim/simulation.hpp>
#include <sim/simulation_flat.hpp>
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
    sheep::set_gene_size(32);   // now deprecated
    sheep::prop.gene_size = 32; // via proxy_type
    sheep::prop.repr_age = 8;
    sheep::prop.threshold = 3;
    sheep::prop.mut_rate = 2;
    N_init[sheep::name] = 1000;
    N_max[sheep::name] = 1000;
    
    // set up bear parameters
    bear::prop.gene_size = 32; // via proxy_type
    bear::prop.repr_age = 8;
    bear::prop.threshold = 3;
    bear::prop.mut_rate = 2;
    N_init[bear::name] = 1000;
    N_max[bear::name] = 1000;
    
    std::map<std::string, int> param;
    
    param["seed"] = util::seed<>();
    
    // This template lambda removes my code duplication from before
    auto fill_param = [&](auto a){
        using A = decltype(a);
        param["N_init_"    + A::name] = N_init[A::name];
        param["N_max_"     + A::name] = N_max[A::name];
        param["gene_size_" + A::name] = A::prop.gene_size;
        param["repr_age_"  + A::name] = A::prop.repr_age;
        param["mut_rate_"  + A::name] = A::prop.mut_rate;
        param["threshold_" + A::name] = A::prop.threshold;
    };
    
     // I need an instance to infuse the type to the template-lambda
     // I dont want to write a normal template, bc [&] is too convenient :)
    fill_param(sheep());
    fill_param(bear());
    
    //~ MIB_START("main")
    //~ MIB_START("ctor")
    
    // now the order of sheep and bear is fine again
    // rename simulation to simulation_flat to test the other implementation
    sim::simulation_flat<zoo_to_sim<sheep>, zoo_to_sim<bear>> pennaLV("pennaLV.txt"
                                                                 , param
                                                                 , N_max
                                                                 , N_init
                                                                 , ""
                                                                 );
    
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
