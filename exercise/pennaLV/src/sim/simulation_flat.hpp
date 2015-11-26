/** ****************************************************************************
 * 
 * \file
 * \brief Simulation Class Declaration with pass-trick
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright For free use, no rights reserved, with no warranty whatsoever.
 *
 ******************************************************************************/

#ifndef SIM_SIMULATION_FLAT_HEADER
#define SIM_SIMULATION_FLAT_HEADER

#include <animal_concept.hpp>
#include <sim_typedef.hpp>

//~ #include <util/profiler.hpp>

#include <map>
#include <list>
#include <fstream>
#include <iostream>

// documented in simulation.hpp
namespace sim {
    /// \cond IMPLEMENTATION_DETAIL_DOC
    namespace detail {
        template<typename T, typename... TX>
        struct first_of {
            using type = T;
        };

        struct pass { // only has a variadic constructor
            template<typename... TN>
            pass(TN const &...) {}
        };
    }//end namespace detail
    /// \endcond
    
    /// \brief does the same as \link simulation \endlink , but differs in implementation details.
    template<typename... Args>
    class simulation_flat {
    public:
        using count_array = typename detail::first_of<Args...>::type::count_array;
        // structors
        /// \brief see simulation::simulation
        simulation_flat( std::string const & file
                       , std::map<std::string, std::string> const & param
                       , std::map<std::string, uint64_t> const & N_max
                       , std::map<std::string, uint64_t> const & N_init
        ): of_(file)
         , N_max_()
         , N_init_()
         , N_t_() {
            
            auto init_N = [&]( count_type const & idx
                             , uint64_t const & init
                             , uint64_t const & max) {
                                 N_max_[idx] = max;
                                 N_init_[idx] = init;
                                 return 0; // is needed bc of pass trick
                             };
            detail::pass{init_N(Args::index, N_init.at(Args::name), N_max.at(Args::name))...};
            
            of_ << "time";
            auto write_name = [&](std::string const & s){of_ << " " << s; return 0;};
            
            // {} instead of () is extremely important with this technique
            detail::pass{write_name(Args::name)...};
            
            of_ << "#param";
            for(auto const & p: param)
                of_ << " " << p.first << " " << p.second;
            of_ << std::endl;

            detail::pass{init_pop_helper<Args>()...};
        }
        // modifying methods
        /// \brief see simulation::run
        void run(uint32_t const & N_generation) {
            auto write_N_t = [&](const int idx){of_ << " " << N_t_[idx]; return 0;};
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
                of_ << i << " ";
                detail::pass{write_N_t(Args::index)...};
                of_ << std::endl;
                //~ MIB_STOP("of")
            }
            of_.close();
        }
        // const methods
        /// \brief see simulation::print
        void print() const {
            // print population size
            detail::pass{print_count_helper<Args>()...};
            if(pop_.size())
                std::cout << "last " << pop_.back() << std::endl;
        }
    private:
        // helper functions that only take type A
        template<typename A>
        int init_pop_helper() {
            for(uint64_t i = 0; i < N_init_[A::index]; ++i) {
                pop_.emplace_back(A(A::random_age()));
            }
            N_t_[A::index] += N_init_[A::index];
            return 0; // is needed bc of pass trick
        }
        template<typename A>
        int print_count_helper() const {
            std::cout << A::name << " count " << N_t_[A::index] << std::endl;
            return 0; // is needed bc of pass trick
        }
    private:
        std::ofstream of_;
        std::list<animal_concept<count_array>> pop_;
        count_array N_max_;
        count_array N_init_;
        count_array N_t_;
    };
}//end namespace sim

#endif //SIM_SIMULATION_FLAT_HEADER
