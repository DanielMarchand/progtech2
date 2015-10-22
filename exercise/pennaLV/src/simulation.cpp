/*******************************************************************************
 *
 * Simulation Class Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <simulation.hpp>

#include <zoo/bear.hpp>
#include <zoo/sheep.hpp>

namespace sim {
    simulation::simulation( std::string const & file
                          , uint64_t const & seed
                          , std::map<std::string, uint64_t> const & N_max
                          , std::map<std::string, uint64_t> const & N_init
        ): of_(file)
         , N_max_{N_max.at(zoo::sheep::name), N_max.at(zoo::bear::name)}
         , N_init_{N_init.at(zoo::sheep::name), N_init.at(zoo::bear::name)}
         , N_t_() {
        using namespace zoo;
        of_ << "time sheep bear" << std::endl;
        
        of_ << "#param"
            << " seed " << seed
            << " N_init " << N_init_[tag::sheep]
            << " N_max " << N_max_[tag::sheep]
            << " gene_size " << sheep::prop.gene_size
            << " repr_age " << sheep::prop.repr_age
            << " mut_rate " << sheep::prop.mut_rate
            << " threshold " << sheep::prop.threshold
            << " N_init_b " << N_init_[tag::bear]
            << " N_max_b " << N_max_[tag::bear]
            << " gene_size_b " << bear::prop.gene_size
            << " repr_age_b " << bear::prop.repr_age
            << " mut_rate_b " << bear::prop.mut_rate
            << " threshold_b " << bear::prop.threshold
            << std::endl;
        
        // generate initial population
        for(uint64_t i = 0; i < N_init_[0]; ++i) {
            pop_.push_back(std::make_shared<sheep>(sheep::random_age()));
        }
        N_t_[tag::sheep] += N_init_[tag::sheep];
        
        for(uint64_t i = 0; i < N_init_[1]; ++i) {
            pop_.push_back(std::make_shared<bear>(bear::random_age()));
        }
        N_t_[tag::bear] += N_init_[tag::bear];
    }

    // modifying methods
    void simulation::run(uint32_t const & N_generation) {
        using namespace zoo;
        for(uint32_t i = 0; i < N_generation; ++i) {
            for(auto it = pop_.begin();  it != pop_.end(); ++it) {
                auto & ap = (*it);
                
                auto dead = not ap->progress(N_max_, N_t_);
                if(dead) {
                    --N_t_[ap->index()];
                    it = pop_.erase(it);
                    --it;
                } else {
                    if(ap->adult()) {
                        ++N_t_[ap->index()];
                        pop_.push_front(ap->make_child());
                    }
                }
            }
            of_ << i << " " << N_t_[0] << " " << N_t_[1] << std::endl;
        }
        of_.close();
    }
    // const methods
    void simulation::print() const {
        // print population size
        std::cout << "sheep count " << N_t_[0] << std::endl;
        std::cout << "bear  count " <<  N_t_[1] << std::endl;
        if(pop_.size())
            std::cout << "last " << *pop_.back() << std::endl;

    }
}//end namespace sim
