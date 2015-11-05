// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:30:51 CET
// File:    animal.hpp

#ifndef ANIMAL_HEADER
#define ANIMAL_HEADER

#include "global.hpp"
#include "../../penna/extern/include/util/random.hpp"

#include <assert.h>
#include <vector>
#include <functional>

namespace zoo {
    //------------------- forward decl -------------------
    class animal;
    //=================== species class ===================
    struct species {
        // structors
        species(opt::age_type const & gene_size
              , opt::age_type const & repr_age
              , opt::mut_type const & threshold
              , opt::mut_type const & mut_rate
              , opt::cnt_type const & N_max
              , opt::cnt_type * const  N_t
              ):
          gene_size(gene_size)
        , repr_age(repr_age)
        , threshold(threshold)
        , mut_rate(mut_rate)
        , N_max(N_max)
        , N_t(N_t)
        , gene_rng(0, gene_size-1) {}
        
        // modifying methods
        // const methods
    
        opt::age_type const gene_size;
        opt::age_type const repr_age;
        opt::mut_type const threshold;
        opt::mut_type const mut_rate;
        opt::cnt_type const N_max;
        opt::cnt_type * const N_t;
        
        std::function<double()> interaction;
        
        util::rng_class<opt::age_type> gene_rng;
    };
    
    //=================== dual pointer ===================
    union dual_ptr {
        species * spec;
        animal * next_dead;
    };
    
    //=================== animal class ===================
    struct animal {
        // structors
        animal(species * const spec): dual({spec})
                                    , age(0)
                                    , bad_genes_(0)
                                    , gene_(dual.spec->gene_size) 
                                    {}
        animal(species * const spec, std::vector<bool> const & gene): dual({spec})
                                                                    , age(0)
                                                                    , bad_genes_(0)
                                                                    , gene_(gene)
                                                                    {}
        animal(species * const spec, opt::age_type const & age): dual({spec})
                                                               , age(age)
                                                               , bad_genes_(0)
                                                               , gene_(dual.spec->gene_size)
                                                               {}
        
        animal(animal const &) noexcept = delete; // dont even try to copy
        animal(animal &&) noexcept = default;                 // move support
        animal & operator=(animal &&) noexcept = default;     // move support
        // modifying methods
        bool progress() {
            bad_genes_ += gene_[age];
            ++age;

            if(bad_genes_ >= dual.spec->threshold) { // darwin selection
                return false;
            }
            
            if(prob_rng() > (1 - double(*dual.spec->N_t) / dual.spec->N_max)) { // resource selection
                return false;
            }
            if(age == dual.spec->gene_size) { // too old
                return false;
            }
            if(prob_rng() > dual.spec->interaction()) {
                return false;
            }

            return true;
        }
        // const methods
        bool adult() const {
            return age >= dual.spec->repr_age;
        }
        void make_child_inplace(animal * child) const {
            child->age = 0;
            child->bad_genes_ = 0;
            
            child->dual.spec = dual.spec;
            child->gene_ = gene_; // not optimal yet
            
            for(opt::mut_type i = 0; i < dual.spec->mut_rate; ++i) { // mutate some gene
                auto pos = dual.spec->gene_rng();
                child->gene_[pos] = !child->gene_[pos]; // flip random gene
            }
        }
        animal make_child() const {
            animal child(dual.spec, gene_);
            for(opt::mut_type i = 0; i < dual.spec->mut_rate; ++i) { // mutate some gene
                auto pos = dual.spec->gene_rng();
                child.gene_[pos] = !child.gene_[pos]; // flip random gene
            }
            return std::move(child);
        }
        
        dual_ptr dual;
        
        opt::age_type age;
        static util::rng_class<double> prob_rng;
    private:
        opt::mut_type bad_genes_;
        std::vector<bool> gene_;
        
    };
    util::rng_class<double> animal::prob_rng(0, 1);
}//end namespace 

#endif //ANIMAL_HEADER
