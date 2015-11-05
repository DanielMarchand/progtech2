// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:30:48 CET
// File:    sim.hpp

#ifndef SIM_HEADER
#define SIM_HEADER

#include "animal.hpp"
#include "global.hpp"
#include "../../penna/extern/include/util/profiler.hpp"

#include <vector>
#include <fstream>

namespace sim {
    void pennaLV(uint64_t const & seed
               , std::string const & filename
               , uint64_t const & N_generation
               , opt::age_type const & sheep_gene_size
               , opt::age_type const & sheep_repr_age
               , opt::mut_type const & sheep_threshold
               , opt::mut_type const & sheep_mut_rate
               , opt::cnt_type const & sheep_N_init
               , opt::cnt_type const & sheep_N_max
               , opt::age_type const & bear_gene_size
               , opt::age_type const & bear_repr_age
               , opt::mut_type const & bear_threshold
               , opt::mut_type const & bear_mut_rate
               , opt::cnt_type const & bear_N_init
               , opt::cnt_type const & bear_N_max) {
        
        MIB_START("main")
        MIB_START("ctor")

        
        util::seed<>(seed);
        
        //=================== setup ===================
        opt::cnt_type sheep_N_t;
        opt::cnt_type bear_N_t;
        //------------------- species -------------------
        zoo::species sheep(sheep_gene_size
                         , sheep_repr_age
                         , sheep_threshold
                         , sheep_mut_rate
                         , sheep_N_max
                         , &sheep_N_t
                         );
        zoo::species bear(bear_gene_size
                        , bear_repr_age
                        , bear_threshold
                        , bear_mut_rate
                        , bear_N_max
                        , &bear_N_t
                        );
        
        sheep.interaction = [&](){return 1 - 0.1 * bear_N_t / double(sheep_N_t);};
        bear.interaction = [&](){return sheep_N_t / double(2 * bear_N_t);};
        
        //------------------- pop vector -------------------
        std::vector<zoo::animal> pop;
        pop.reserve(sheep_N_init + bear_N_init); // avoid vector resize
        
        for(opt::cnt_type i = 0; i < sheep_N_init; ++i)
            pop.emplace_back(&sheep, sheep.gene_rng());
        sheep_N_t = sheep_N_init;

        for(opt::cnt_type i = 0; i < bear_N_init; ++i)
            pop.emplace_back(&bear, bear.gene_rng());
        bear_N_t = bear_N_init;
        
        //------------------- results vector -------------------
        std::vector<std::pair<opt::cnt_type, opt::cnt_type>> res;
        res.resize(N_generation);
        
        //~ zoo::animal * first_dead = nullptr;
        //~ zoo::animal * prev_dead = nullptr;
        
        MIB_NEXT("run")
        
        zoo::animal * prev_dead = nullptr;
        zoo::animal * sentinel = nullptr;
        zoo::animal * first_dead = sentinel;
        
        auto dead_count = [&](){
            int i = 0;
            for(zoo::animal * it = first_dead; it != sentinel; it = it->dual.next_dead) {
                assert(it->age == opt::dead);
                ++i;
            }
            return i;
        };
        
        auto state_print = [&]() {
            for(auto const & a: pop)
                std::cout << (a.age != opt::dead);
            std::cout << std::endl;
        };
        
        
        //=================== simulation ===================
        for(uint64_t g = 0; g < N_generation; ++g) {
            prev_dead = nullptr;
            
            for(auto it = pop.begin();  it != pop.end(); ++it) {
                auto & ap = (*it);
                if(ap.age == opt::newborn)
                    ap.age = 0;
                else if(ap.age == opt::dead)
                    prev_dead = &ap;
                else {
                    MIB_START("prog")
                    auto dead = not ap.progress();
                    MIB_STOP("prog")
                    if(dead) {
                        MIB_START("dead")
                        --(*(ap.dual.spec->N_t));
                        if(prev_dead == nullptr) {
                            ap.dual.next_dead = first_dead;
                            first_dead = &ap;
                        } else {
                            zoo::animal * next_dead = prev_dead->dual.next_dead;
                            ap.dual.next_dead = next_dead;
                            prev_dead->dual.next_dead = &ap;
                        }
                        ap.age = opt::dead;
                        prev_dead = &ap;
                        MIB_STOP("dead")
                    } else {
                        if(ap.adult()) {
                            MIB_START("birth")
                            if(first_dead != sentinel) {
                                zoo::animal * next_dead = first_dead->dual.next_dead;
                                ap.make_child_inplace(first_dead);
                                if(first_dead > &ap)
                                    first_dead->age = opt::newborn;
                                if(first_dead == prev_dead)
                                    prev_dead = nullptr;
                                first_dead = next_dead;
                                
                            } else {
                                assert(false);
                                pop.push_back(ap.make_child());
                                pop.back().age = opt::newborn;
                            }
                            ++(*(ap.dual.spec->N_t));
                            MIB_STOP("birth")
                        }
                    }
                }
            }
            res[g] = std::make_pair(sheep_N_t, bear_N_t);
        }
        
        //=================== write to file ===================
        MIB_START("of")
        std::ofstream of(filename);
        of << "time sheep bear" << std::endl;
        of << "#param"
           << " seed " << seed
           << " N_init_sheep "    << sheep_N_init
           << " N_max_sheep "     << sheep_N_max
           << " gene_size_sheep " << sheep_gene_size
           << " repr_age_sheep "  << sheep_repr_age
           << " mut_rate_sheep "  << sheep_mut_rate
           << " threshold_sheep " << sheep_threshold
           << " N_init_bear "     << bear_N_init
           << " N_max_bear "      << bear_N_max
           << " gene_size_bear "  << bear_gene_size
           << " repr_age_bear "   << bear_repr_age
           << " mut_rate_bear "   << bear_mut_rate
           << " threshold_bear "  << bear_threshold
           << std::endl;
        
        for(uint64_t g = 0; g < N_generation; ++g) {
            of << g << " " << res[g].first << " " << res[g].second << std::endl;
        }
        of.close();
        
        MIB_STOP("of")
        MIB_NEXT("print")
        
        std::cout << "sheep count " << sheep_N_t << std::endl;
        std::cout << "bear count " << bear_N_t << std::endl;
    
        MIB_STOP("print")
        MIB_STOP("main")
    
        MIB_PRINT("cycle")
        MIB_SAVE("cycle", "fast_vec_O3.txt")
    }
}//end namespace sim

#endif //SIM_HEADER
