// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:30:48 CET
// File:    sim.hpp

#ifndef SIM_HEADER
#define SIM_HEADER

#include "animal.hpp"
#include "global.hpp"
#include "ctc/ctc_random.hpp"
#include "ctc/ctc_utils.hpp"

#include <vector>
#include <fstream>

namespace sim {
    template<opt::cnt_type sheep_N_max
           , opt::cnt_type bear_N_max
           , uint64_t N_generation>
    constexpr ctc::static_vector<ctc::pair<opt::cnt_type, opt::cnt_type>
                               , N_generation
                               > pennaLV(uint64_t const & seed
                         , opt::age_type const & sheep_gene_size
                         , opt::age_type const & sheep_repr_age
                         , opt::mut_type const & sheep_threshold
                         , opt::mut_type const & sheep_mut_rate
                         , opt::cnt_type const & sheep_N_init
                         , opt::age_type const & bear_gene_size
                         , opt::age_type const & bear_repr_age
                         , opt::mut_type const & bear_threshold
                         , opt::mut_type const & bear_mut_rate
                         , opt::cnt_type const & bear_N_init
                         ) {
        
        ctc::mt19937 engine(seed);
        engine.seed(seed);
        ctc::rng_class<double> prop_rng(0, 1, engine);
        
        //=================== setup ===================
        opt::cnt_type sheep_N_t = 0;
        opt::cnt_type bear_N_t = 0;
        double_void_functor sheep_interaction(sheep_N_t, bear_N_t, true);
        double_void_functor bear_interaction(sheep_N_t, bear_N_t, false);
        //------------------- species -------------------
        zoo::species sheep(sheep_gene_size
                         , sheep_repr_age
                         , sheep_threshold
                         , sheep_mut_rate
                         , sheep_N_max
                         , sheep_N_t
                         , sheep_interaction
                         , engine
                         );
        zoo::species bear(bear_gene_size
                        , bear_repr_age
                        , bear_threshold
                        , bear_mut_rate
                        , bear_N_max
                        , bear_N_t
                        , bear_interaction
                        , engine
                        );
        
        //------------------- pop vector -------------------
        ctc::static_vector<zoo::animal, sheep_N_max + bear_N_max> pop;
        
        for(opt::cnt_type i = 0; i < sheep_N_init; ++i)
            pop.push_back(zoo::animal(&sheep, sheep.gene_rng()));
        sheep_N_t = sheep_N_init;

        for(opt::cnt_type i = 0; i < bear_N_init; ++i)
            pop.push_back(zoo::animal(&bear, bear.gene_rng()));
        bear_N_t = bear_N_init;
        
        //------------------- results vector -------------------
        ctc::static_vector<ctc::pair<opt::cnt_type, opt::cnt_type>, N_generation> res;
        
        zoo::animal * prev_dead = nullptr;
        zoo::animal * sentinel = nullptr;
        zoo::animal * first_dead = sentinel;
        
        //=================== simulation ===================
        for(uint64_t g = 0; g < N_generation; ++g) {
            prev_dead = nullptr;
            
            for(std::size_t i = 0;  i < pop.size(); ++i) {
                auto & ap = pop[i];
                if(ap.age == opt::newborn)
                    ap.age = 0;
                else if(ap.age == opt::dead)
                    prev_dead = &ap;
                else {
                    auto dead = not ap.progress(prop_rng);
                    if(dead) {
                        --(ap.dual.spec->N_t);
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
                    } else {
                        if(ap.adult()) {
                            if(first_dead != sentinel) {
                                zoo::animal * next_dead = first_dead->dual.next_dead;
                                ap.make_child_inplace(first_dead);
                                if(first_dead > &ap)
                                    first_dead->age = opt::newborn;
                                if(first_dead == prev_dead)
                                    prev_dead = nullptr;
                                first_dead = next_dead;
                                
                            } else {
                                pop.push_back(ap.make_child());
                                pop.back().age = opt::newborn;
                            }
                            ++(ap.dual.spec->N_t);
                        }
                    }
                }
            }
            res.push_back(ctc::make_pair(sheep_N_t, bear_N_t));
        }
        
        //~ std::cout << "sheep count " << sheep_N_t << std::endl;
        //~ std::cout << "bear count " << bear_N_t << std::endl;
        return res;
    }
}//end namespace sim

#endif //SIM_HEADER
