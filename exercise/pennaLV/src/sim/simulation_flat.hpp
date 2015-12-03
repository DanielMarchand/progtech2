/** ****************************************************************************
 * 
 * \file
 * \brief Simulation Class Declaration with pass-trick
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 *
 ******************************************************************************/

#ifndef SIM_SIMULATION_FLAT_HEADER
#define SIM_SIMULATION_FLAT_HEADER

#include <animal_concept.hpp>
#include <sim_typedef.hpp>
#include <hdf5_support.hpp>

//~ #include <util/profiler.hpp>

#include <map>
#include <list>
#include <vector>
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
        /**\brief only constructor for simulation
         * \param file  should be a filename where the simulation-output should 
         *        be written to.
         * \param param  is a map of strings and just holds parameter that 
         *        should be written to the file before the simulation starts. 
         *        Could also be done in the main.cpp directly. 
         * \param N_max  maps an animal-name (A::name) to the variable N_max for 
         *        this animal. N_max is the carrying capacity for the penna model.
         * \param N_init  maps an animal-name (A::name) to the variable N_init 
         *        for this animal, which states with how many animals the 
         *        simulation stats.
         * \param h5set if this parameter is given, the simulation will write in hdf5
         *        instead of txt. The name of the hdf5-dataset will be given by this parameter.
         * */
        simulation_flat( std::string const & file
                       , std::map<std::string, int> const & param
                       , std::map<std::string, uint64_t> const & N_max
                       , std::map<std::string, uint64_t> const & N_init
                       , std::string const & h5dset = ""
        ): file_(file)
         , h5dset_(h5dset)
         , param_(param)
         , N_max_()
         , N_init_()
         , N_t_()
        {
            auto init_N = [&]( count_type const & idx
                             , uint64_t const & init
                             , uint64_t const & max) {
                                 N_max_[idx] = max;
                                 N_init_[idx] = init;
                                 return 0; // is needed bc of pass trick
                             };
            detail::pass{init_N(Args::index, N_init.at(Args::name), N_max.at(Args::name))...};
            detail::pass{init_pop_helper<Args>()...};
        }
        // modifying methods
        /// \brief see simulation::run
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
                res_.push_back(std::vector<uint64_t>{i, N_t_[Args::index]...});
                //~ MIB_STOP("of")
            }
            if(h5dset_ == "")
                write_txt();
            else
                write_hdf5();
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
        void write_txt() {
            std::ofstream of(file_);
            
            of << "time";
            auto write_name = [&](std::string const & s){of << " " << s; return 0;};
            
            // {} instead of () is extremely important with this technique
            detail::pass{write_name(Args::name)...};
            
            of << "#param";
            for(auto const & p: param_)
                of << " " << p.first << " " << p.second;
            of << std::endl;
            
            for(auto const & line: res_) {
                for(auto const & elem: line)
                    of << elem << " ";
                of << std::endl;
            }
        }
        void write_hdf5() {
            to_hdf5(file_, h5dset_, res_, param_);
        }
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
        std::string file_;
        std::string h5dset_;
        std::vector<std::vector<uint64_t>> res_;
        std::map<std::string, int> const param_;
        
        std::list<animal_concept<count_array>> pop_;
        count_array N_max_;
        count_array N_init_;
        count_array N_t_;
    };
}//end namespace sim

#endif //SIM_SIMULATION_FLAT_HEADER
