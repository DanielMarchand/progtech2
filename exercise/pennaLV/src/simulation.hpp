/*******************************************************************************
 *
 * Simulation Class Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef SIMULATION_HEADER
#define SIMULATION_HEADER

#include <animal_concept.hpp>
#include <sim_typedef.hpp>

//~ #include <util/profiler.hpp>

#include <map>
#include <list>
#include <fstream>
#include <iostream>

namespace sim {
    template<typename A1, typename A2>
    class simulation {
    public:
        // structors
        simulation( std::string const & file
                  , uint64_t const & seed
                  , std::map<std::string, uint64_t> const & N_max
                  , std::map<std::string, uint64_t> const & N_init
        ): 
           of_(file)
         , N_max_{N_max.at(A1::name), N_max.at(A2::name)}
         , N_init_{N_init.at(A1::name), N_init.at(A2::name)}
         , N_t_() {
            using namespace zoo;
            of_ << "time " << A1::name << " " << A2::name << std::endl;

            of_ << "#param"
                << " seed " << seed;
            of_helper<A1>();
            of_helper<A2>();
            of_ << std::endl;

            // generate initial population
            init_helper<A1>();
            init_helper<A2>();
        }
        // modifying methods
        void run(uint32_t const & N_generation) {
            for(uint32_t i = 0; i < N_generation; ++i) {
                for(auto it = pop_.begin();  it != pop_.end(); ++it) {
                    auto & ap = (*it);
                    
                    //~ MIB_START("prog")
                    auto dead = not ap.progress(N_max_, N_t_);
                    //~ MIB_STOP("prog")
                    if(dead) {
                        //~ MIB_START("dead")
                        --N_t_[ap.index()];
                        it = pop_.erase(it);
                        --it;
                        //~ MIB_STOP("dead")
                    } else {
                        if(ap.adult()) {
                            //~ MIB_START("birth")
                            ++N_t_[ap.index()];
                            pop_.push_front(ap.make_child());
                            //~ MIB_STOP("birth")
                        }
                    }
                }
                //~ MIB_START("of")
                of_ << i << " " << N_t_[A1::index] << " " << N_t_[A2::index] << std::endl;
                //~ MIB_STOP("of")
            }
            of_.close();
        }
        // const methods
        inline count_array const & N_t() const {
            return N_t_;
        }
        void print() const {
            // print population size
            std::cout << A1::name << " count " << N_t_[A1::index] << std::endl;
            std::cout << A2::name << " count " << N_t_[A2::index] << std::endl;
            if(pop_.size())
                std::cout << "last " << pop_.back() << std::endl;
        }
    private:
        // helper functions that only take type AX
        template<typename AX>
        void of_helper() {
            of_ << " N_init_"    << AX::name << " " << N_init_[AX::index]
                << " N_max_"     << AX::name << " " << N_max_[AX::index]
                << " gene_size_" << AX::name << " " << AX::prop.gene_size
                << " repr_age_"  << AX::name << " " << AX::prop.repr_age
                << " mut_rate_"  << AX::name << " " << AX::prop.mut_rate
                << " threshold_" << AX::name << " " << AX::prop.threshold;
        }
        
        template<typename AX>
        void init_helper() {
            for(uint64_t i = 0; i < N_init_[AX::index]; ++i) {
                pop_.emplace_back(AX(AX::random_age()));
            }
            N_t_[AX::index] += N_init_[AX::index];
        }

    private:
        std::ofstream of_;
        std::list<animal_concept> pop_;
        count_array N_max_;
        count_array N_init_;
        count_array N_t_;
    };
}//end namespace sim

#endif //SIMULATION_HEADER
