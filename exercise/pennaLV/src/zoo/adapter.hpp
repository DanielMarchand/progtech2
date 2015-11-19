/*******************************************************************************
 *
 * adapter to simulation
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef ADAPTER_HEADER
#define ADAPTER_HEADER

#include "zoo.hpp"
#include "animal_crtp.hpp"

// documented in zoo.hpp
namespace zoo {

    /** \brief Adapter to the sim::animal_concept.
     *  \tparam T  Animal type to adapt.
     *  \details This wrapper allows the interface implemented by the zoo library
     *  to be used by the sim::simulation class.
     *  \n\b Example:
     *  ~~~{.cpp}
     *      sim::simulation< zoo::zoo_to_sim<zoo::sheep> > s;
     *  ~~~
     *  The members and method signatures correspond to sim::animal_concept.
     */
    //! \{
    template<typename T>
    class zoo_to_sim {
        public:
        
        using count_array = typename T::count_array; ///< &nbsp;
        
        zoo_to_sim(age_type const & age = 0): t_(age) {}

        // copy ctor implicitly deleted by move, enable if needed
        zoo_to_sim(zoo_to_sim && rhs) noexcept = default; // for clarity

        // modifying methods
        bool progress(count_array const & N_max
                    , count_array const & N_t) {
            return t_.progress(N_max, N_t);
        }
        inline static age_type random_age() {
            return T::random_age();
        }

        static void set_gene_size(age_type const & gene_size) {
            T::set_gene_size(gene_size);
        }
        // const methods
        bool adult() const { return t_.adult(); }
        
        T make_child() const { return t_.make_child(); }
        void print(std::ostream & os) const { t_.print(os); }
        
        public:
        static const std::string & name;
        static const tag::animal_enum index = T::index;
        private:
        T t_;
    };

    template<typename T>
    std::string const & zoo_to_sim<T>::name = T::name;
    
    template<typename T>
    std::ostream & operator<<(std::ostream & os, zoo_to_sim<T> const & arg) {
        arg.print(os);
        return os;
    }
    //! \}
}//end namespace zoo

#endif //ADAPTER_HEADER
