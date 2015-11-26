/** ****************************************************************************
 * 
 * \file
 * \brief CRTP animal declaration & implementation
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#ifndef ZOO_ANIMAL_CRTP_HEADER
#define ZOO_ANIMAL_CRTP_HEADER

#include "zoo.hpp"
#include <util/random.hpp>

#include <memory>
#include <iostream>

// TODO: move to general helper header
/// \brief This macro just warns the user once if it is encountered during runtime
#define DEPRECATED(msg)            \
static bool derpr_warned = false;  \
if(not derpr_warned) {             \
    derpr_warned = true;           \
    std::clog << msg << std::endl; \
}                                  //

// documented in zoo.hpp
namespace zoo {

    // typedefs (we still call them typedefs even if we dont use typedef)
    using age_type = uint32_t;   ///< &nbsp;
    using mut_type = uint32_t;   ///< &nbsp;
    
    /** \brief CRTP base class for zoo animals
     *  \tparam T  Concrete type of animal to curiously recur upon.
     *  \details This class is used as base for zoo::sheep and zoo::bear.
     */
    template<typename T>
    class animal_crtp {
        
        struct gene_proxy_type { // should behave like an age_type
            // the proxy can be casted implicitly to age_type
            operator age_type() {
                return gene_size_;
            }
            // and sets the gene_rng if the value is changed
            gene_proxy_type & operator=(age_type const & gene_size) {
                gene_size_ = gene_size;
                gene_rng.set_range(0, gene_size_ - 1);
                return (*this);
            }
            age_type gene_size_;
        };
        
        public:
        /** \brief Properties of an animal species
         *  \details This used in zoo::animal_crtp (e.g. zoo::sheep) and must be initialised
         *  by the user.\n\b Example:
         *  ~~~{.cpp}
         *      zoo::sheep::prop.repr_age = 8;
         *  ~~~
         */
        struct species_properties {
            gene_proxy_type gene_size; ///< genome length
            age_type repr_age;         ///< age above which the animal is allowed to reproduce
            mut_type threshold;        ///< number of bad genes that are survivable
            mut_type mut_rate;         ///< rate of gene mutation
        };
        
        using count_array = std::array<uint64_t, zoo::tag::N_animal>; ///< &nbsp;
        
        /** \brief Construct an animal
         *  \param age  of the new animal in years (default = 0).
         *  \param gene_size  of the animal (default = prop.gene_size from species_properties).
         *  \details This will initialise a new animal with randomised genes.
         *  \n\b Example:
         *  ~~~{.cpp}
         *      zoo::sheep::prop.mut_rate = 2;
         *      // ...
         *      zoo::animal_crtp<zoo::sheep> s;
         *  ~~~
         */
        animal_crtp(age_type const & age = 0,
                    age_type const & gene_size = prop.gene_size):
                      age_(age)
                    , bad_genes_(0)
                    , gene_(gene_size) {}
        virtual ~animal_crtp() {} // virtual here is important!

        /** \brief Defaulted move constructor.
         *  \warning Copy constructor implicitly deleted by move, enable in case
         *           it is needed.
         */
        animal_crtp(animal_crtp && rhs) noexcept = default; // for clarity

        // modifying methods

        /** \brief Progress the lifetime of an animal by one time unit.
         *  \param N_max  List of population maximum values per species.
         *  \param N_t    List of current population counts.
         *  \return       boolean describing if the animal should be considered still alive
         *  \details This will increase the age of the animal and accumulate the
         *  bad genes.\n
         *  The animal will die (returns `false`) if the bad gene count
         *  exceeds the species_properties::threshold, if the population maximum
         *  has been reached or depending on a species-specific animal interaction.
         */
        bool progress(count_array const & N_max
                    , count_array const & N_t) {
            bad_genes_ += gene_[age_];
            age_ += 1;

            if(bad_genes_ >= prop.threshold) { // darwin selection
                return false;
            }
            
            if(prob_rng() > (1 - double(N_t[T::index]) / N_max[T::index])) { // resource selection
                return false;
            }
            if(age_ == prop.gene_size) { // too old
                return false;
            }
            if(prob_rng() > T::interaction(N_t)) {
                return false;
            }

            return true;
        }

        // const methods

        /** \return whether the animal is considered adult (fit for reproduction)
         */
        inline bool adult() const {
            return age_ >= prop.repr_age;
        }
        /** \brief Create offspring
         *  \returns a child of the animal
         *  \details The offspring's genes will be slight mutations (depending
         *  on species_properties::mut_rate) of the parent's.
         */
        T make_child() const {
            T child;
            child.gene_ = gene_; // copy gene

            for(mut_type i = 0; i < prop.mut_rate; ++i) { // mutate some gene
                auto pos = gene_rng();
                child.gene_[pos] = !child.gene_[pos]; // flip random gene
            }
            return std::move(child);
        }

        /** \brief Print a human-readable representation.
         *  \param os  The stream to write to.
         */
        void print(std::ostream & os) const {
            os << T::name << ": (age: " << age_ << "): ";
            for(age_type i = 0; i < gene_.size(); ++i) {
                os << "\033[0;";
                if(i < age_) { // these blocks just generate colors
                    if(gene_[i])
                        os << "41m";
                    else
                        os << "42m";
                }
                else {
                    if(gene_[i])
                        os << "31m";
                    else
                        os << "32m";
                }
                // actual print
                os << gene_[i] << "\033[0m";
            }
        }

        // static methods

        /** \brief Exposes random age generator
         *  \returns a random number in [0, prop::gene_size)
         *  \details The maximum age is implementation-bound by
         *  species_properties::gene_size due to the amount of mutations the gene
         *  can accrue over its life time.\n
         *  This is used to construct the animals\n\b Example:
         *  ~~~{.cpp}
         *       using namespace zoo;
         *       std::list<sheep> population;
         *       population.emplace_back(sheep(sheep::random_age()));
         *  ~~~
         */
        inline static age_type random_age() {
            return gene_rng();
        }

        /** \deprecated prop.gene_size is now a proxy that takes care of setting the
         *  propper random number range.
         *  ~~~{.cpp}
         *      zoo::sheep::prop.gene_size = 2;
         *  ~~~
         *  works now perfectly fine.
         *  \brief Set gene size
         *  \param gene_size  Length of the animal gene.
         *  \details This function must be used to set the species_properties::gene_size.\n
         *  If the gene_size of an animal is set directly via assignment operator,
         *  the random number generator responsible for aging mutation (progress())
         *  will provide wrong numbers.
         *  \n\b BAD Example:
         *  ~~~{.cpp}
         *       zoo::sheep::prop.gene_size = 2;
         *  ~~~
         *  Instead one should use this setter:
         *  ~~~{.cpp}
         *       zoo::sheep::set_gene_size(2);
         *  ~~~
         *  
         */
        static void set_gene_size(age_type const & gene_size) {
            DEPRECATED("Warning: set_gene_size is marked as deprecated")
            prop.gene_size = gene_size;
            gene_rng.set_range(0, prop.gene_size - 1);
        }

        // static members
        public:
        /// species_properties member.
        static species_properties prop;
        /// Tag used by zoo::tag::animal_enum for the count array.
        static const tag::animal_enum N_animal = tag::N_animal;

        private:
        static util::rng_class<age_type> gene_rng;
        static util::rng_class<double> prob_rng;

        // members
        protected: // derived class need access
        age_type age_;               ///< current age of the animal
        mut_type bad_genes_;         ///< amount of bad genes accumulated so far
        std::vector<bool> gene_;     ///< the gene representation

    };

    // static members
    template<typename T>
    typename animal_crtp<T>::species_properties animal_crtp<T>::prop;

    // gene_rng has to be set again via set_gene_size
    template<typename T>
    util::rng_class<age_type> animal_crtp<T>::gene_rng(0, animal_crtp<T>::prop.gene_size - 1);

    template<typename T>
    util::rng_class<double> animal_crtp<T>::prob_rng(0, 1);

    /**\brief wraps the animal print function
     * \param os  std::cout or any std::ostream instance
     * \param arg  an animal_concept instance
     * \return the ostream reference to \c os
     */
    template<typename D>
    std::ostream & operator<<(std::ostream & os, animal_crtp<D> const & arg) {
        arg.print(os);
        return os;
    }

}//end namespace zoo

#endif // ZOO_ANIMAL_CRTP_HEADER
