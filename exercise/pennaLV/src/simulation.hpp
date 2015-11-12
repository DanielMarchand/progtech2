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
    //=================== simulation implementation ===================
    // variadic sim
    template<typename CA, typename... A>
    class simulation_impl;
    
    //------------------- empty specialization -------------------
    template<typename CA>
    class simulation_impl<CA> {
        using count_array = CA;
    public:
        // structors
        simulation_impl( std::string const & file
                       , std::map<std::string, uint64_t> const &
                       , std::map<std::string, uint64_t> const &
        ): of_(file)
         , N_max_()
         , N_init_()
         , N_t_() {
            of_ << "time";
        }
        // const methods
        inline count_array const & N_t() const {
            return N_t_;
        }
    protected:
        // we only want to use these functions in the sub-class
        void of_print_index() {}
        void print() const {}
    protected:
        // we need access from the sub-class
        std::ofstream of_;
        std::list<animal_concept<count_array>> pop_;
        count_array N_max_;
        count_array N_init_;
        count_array N_t_;
    };
    
    //------------------- recursive specialization -------------------
    template<typename CA, typename A, typename... Rest>
    class simulation_impl<CA, A, Rest...>: public simulation_impl<CA, Rest...> {
        
        using super = simulation_impl<CA, Rest...>;
        
    protected:
        // I'm to lazy to write super::xy all the time
        using super::of_;
        using super::pop_;
        using super::N_max_;
        using super::N_init_;
        using super::N_t_;
        
    public:
        // structors
        simulation_impl( std::string const & file
                       , std::map<std::string, uint64_t> const & N_max
                       , std::map<std::string, uint64_t> const & N_init
        ): super(file, N_max, N_init) {
            of_ << " " << A::name;
            N_init_[A::index] = N_init.at(A::name);
            N_max_[A::index] = N_max.at(A::name);
            
            for(uint64_t i = 0; i < N_init_[A::index]; ++i) {
                pop_.emplace_back(A(A::random_age()));
            }
            N_t_[A::index] += N_init_[A::index];
        }
    protected:
        void of_print_index() {
            super::of_print_index();
            of_ << " " << N_t_[A::index];
            
        }
        void print() const {
            super::print();
            std::cout << A::name << " count " << N_t_[A::index] << std::endl;
        }
    };
    
    //=================== lowest class ===================
    template<typename A, typename... Rest>
    class simulation: public simulation_impl<typename A::count_array, A, Rest...> {
        
        using super = simulation_impl<typename A::count_array, A, Rest...>;
    
    protected:
        using super::of_;
        using super::pop_;
        using super::N_max_;
        using super::N_init_;
        using super::N_t_;
            
    public:
        // structors
        simulation( std::string const & file
                  , std::map<std::string, std::string> const & param
                  , std::map<std::string, uint64_t> const & N_max
                  , std::map<std::string, uint64_t> const & N_init
        ): super(file, N_max, N_init) {
            
            of_ << std::endl;
            of_ << "#param";
            
            for(auto const & p: param) {
                of_ << " " << p.first << " " << p.second;
            }
            
            of_ << std::endl;
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
                of_ << i;
                super::of_print_index();
                of_ << std::endl;
                //~ MIB_STOP("of")
            }
            of_.close();
        }
        // const methods
        void print() const {
            // print population size
            super::print();
            if(pop_.size())
                std::cout << "last " << pop_.back() << std::endl;
        }
    };
}//end namespace sim

#endif //SIMULATION_HEADER
