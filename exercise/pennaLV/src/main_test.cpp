/** ****************************************************************************
 * 
 * \file
 * \brief Main unit test
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * \cond IMPLEMENTATION_DETAIL_DOC
 * 
 ******************************************************************************/

#include <zoo/bear.hpp>
#include <zoo/sheep.hpp>
#include <zoo/adapter.hpp>
#include <sim/simulation.hpp>
#include <util/random.hpp>

#include <map>
#include <list>

#include <catch.hpp>

TEST_CASE("Functional Test of main", "[mainTest]") {
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
    
    sim::simulation<zoo_to_sim<sheep>, zoo_to_sim<bear>> pennaLV("pennaLV.txt"
                                                                , param
                                                                , N_max
                                                                , N_init);
    
    pennaLV.run(300);
    
    // Check end of simulation
    INFO("Some of your numerics changed! Might be a bug or not!");
    CHECK(pennaLV.N_t()[0] == 108);
    CHECK(pennaLV.N_t()[1] == 57);

}
