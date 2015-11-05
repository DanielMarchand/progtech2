// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    30.10.2015 12:30:51 CET
// File:    animal.hpp

#ifndef ANIMAL_HEADER
#define ANIMAL_HEADER

#include "global.hpp"
#include "ctc/ctc_random.hpp"
#include "ctc/ctc_utils.hpp"

#include <assert.h>
#include <vector>
#include <functional>

struct double_void_functor {
    constexpr double_void_functor(opt::cnt_type & N_sheep
                                , opt::cnt_type & N_bear
                                , bool const & sheep): sheep_N_t(N_sheep)
                                                     , bear_N_t(N_bear)
                                                     , sheep_impl(sheep) {
    }
    constexpr double operator()() {
        if(sheep_impl)
            return 1 - 0.1 * bear_N_t / double(sheep_N_t);
        else
            return sheep_N_t / double(2 * bear_N_t);
    }
    
    opt::cnt_type & sheep_N_t;
    opt::cnt_type & bear_N_t;
    const bool sheep_impl;
    
};


namespace zoo {
    //------------------- forward decl -------------------
    class animal;
    //=================== species class ===================
    struct species {
        // structors
        constexpr species(opt::age_type const & gene_size
                        , opt::age_type const & repr_age
                        , opt::mut_type const & threshold
                        , opt::mut_type const & mut_rate
                        , opt::cnt_type const & N_max
                        , opt::cnt_type & N_t
                        , double_void_functor & fct
                        , ctc::mt19937 & engine
                        ):
          gene_size(gene_size)
        , repr_age(repr_age)
        , threshold(threshold)
        , mut_rate(mut_rate)
        , N_max(N_max)
        , N_t(N_t)
        , interaction(fct)
        , gene_rng(0, gene_size-1, engine) {}
        
        // modifying methods
        // const methods
    
        opt::age_type const gene_size;
        opt::age_type const repr_age;
        opt::mut_type const threshold;
        opt::mut_type const mut_rate;
        opt::cnt_type const N_max;
        opt::cnt_type & N_t;
        
        double_void_functor & interaction;
        
        ctc::rng_class<opt::age_type> gene_rng;
    };
    
    //=================== dual pointer ===================
    union dual_ptr {
        species * spec;
        animal * next_dead;
    };
    
    //=================== animal class ===================
    struct animal {
        // structors
        constexpr animal(species * const spec): dual({spec})
                                    , age(0)
                                    , bad_genes_(0)
                                    , gene_(dual.spec->gene_size) 
                                    {}
        constexpr animal(): dual({nullptr})
                                    , age(opt::dead)
                                    , bad_genes_(0)
                                    , gene_()
                                    {}
        constexpr animal(species * const spec, ctc::static_vector<bool, opt::max_gene> const & gene): dual({spec})
                                                                    , age(0)
                                                                    , bad_genes_(0)
                                                                    , gene_(gene)
                                                                    {}
        constexpr animal(species * const spec, opt::age_type const & age): dual({spec})
                                                               , age(age)
                                                               , bad_genes_(0)
                                                               , gene_(dual.spec->gene_size)
                                                               {}
        
        constexpr animal & operator=(animal const & rhs) {
            age = rhs.age;
            dual = rhs.dual;
            bad_genes_ = rhs.bad_genes_;
            gene_ = rhs.gene_;
            return (*this);
        }
        //~ // modifying methods
        constexpr bool progress(ctc::rng_class<double> & prob_rng) {
            bad_genes_ += gene_[age];
            ++age;

            if(bad_genes_ >= dual.spec->threshold) { // darwin selection
                return false;
            }
            
            if(prob_rng() > (1 - double(dual.spec->N_t) / dual.spec->N_max)) { // resource selection
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
        constexpr bool adult() const {
            return age >= dual.spec->repr_age;
        }
        constexpr void make_child_inplace(animal * child) const {
            child->age = 0;
            child->bad_genes_ = 0;
            
            child->dual.spec = dual.spec;
            child->gene_ = gene_; // not optimal yet
            
            for(opt::mut_type i = 0; i < dual.spec->mut_rate; ++i) { // mutate some gene
                auto pos = dual.spec->gene_rng();
                child->gene_[pos] = !child->gene_[pos]; // flip random gene
            }
        }
        constexpr animal make_child() const {
            animal child(dual.spec, gene_);
            for(opt::mut_type i = 0; i < dual.spec->mut_rate; ++i) { // mutate some gene
                auto pos = dual.spec->gene_rng();
                child.gene_[pos] = !child.gene_[pos]; // flip random gene
            }
            return std::move(child);
        }
        
        
        dual_ptr dual;
        opt::age_type age;
        
    private:
        opt::mut_type bad_genes_;
        ctc::static_vector<bool, opt::max_gene> gene_;
        
    };
    //~ ctc::rng_class<double> animal::prob_rng(0, 1);
}//end namespace 

#endif //ANIMAL_HEADER
