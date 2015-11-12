/*******************************************************************************
 *
 * Animal CRTP Base
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef ANIMAL_CRTP_HEADER
#define ANIMAL_CRTP_HEADER

#include "zoo.hpp"
#include <util/random.hpp>

#include <memory>
#include <iostream>

namespace zoo {

    // typedefs (we still call them typedefs even if we dont use typedef)
    using age_type = uint32_t;
    using mut_type = uint32_t;

    // define this struct only once 
    struct species_properties {
        age_type gene_size; // not optimal, but max_age and gene_size are connected
        age_type repr_age;
        mut_type threshold;
        mut_type mut_rate;
    };

    template<typename T>
    class animal_crtp {
        public:
        
        using count_array = std::array<uint64_t, zoo::tag::N_animal>;
        
        // structors
        animal_crtp(age_type const & age = 0,
                    age_type const & gene_size = prop.gene_size):
                      age_(age)
                    , bad_genes_(0)
                    , gene_(gene_size) {}
        virtual ~animal_crtp() {} // virtual here is important!

        // copy ctor implicitly deleted by move, enable if needed
        animal_crtp(animal_crtp && rhs) noexcept = default; // for clarity

        // modifying methods
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
        inline bool adult() const {
            return age_ >= prop.repr_age;
        }
        inline tag::animal_enum index() const {
            return T::index;
        }
        T make_child() const {
            T child;
            child.gene_ = gene_; // copy gene

            for(mut_type i = 0; i < prop.mut_rate; ++i) { // mutate some gene
                auto pos = gene_rng();
                child.gene_[pos] = !child.gene_[pos]; // flip random gene
            }
            return std::move(child);
        }

        inline std::string name() const {
            return T::name;
        }

        void print(std::ostream & os) const {
            os << name() << ": (age: " << age_ << "): ";
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
        inline static age_type random_age() {
            return gene_rng();
        }

        static void set_gene_size(age_type const & gene_size) {
            prop.gene_size = gene_size;
            gene_rng.set_range(0, prop.gene_size - 1);
        }

        // static members
        public:
        static species_properties prop;
        static const tag::animal_enum N_animal = tag::N_animal;
        private:
        static util::rng_class<age_type> gene_rng;
        static util::rng_class<double> prob_rng;

        // members
        protected: // derived class need access
        age_type age_;
        mut_type bad_genes_;
        std::vector<bool> gene_;

    };

    // static members
    template<typename T>
    species_properties animal_crtp<T>::prop;

    // gene_rng has to be set again via set_gene_size
    template<typename T>
    util::rng_class<age_type> animal_crtp<T>::gene_rng(0, animal_crtp<T>::prop.gene_size - 1);

    template<typename T>
    util::rng_class<double> animal_crtp<T>::prob_rng(0, 1);

    // printing
    template<typename D>
    std::ostream & operator<<(std::ostream & os, animal_crtp<D> const & arg) {
        arg.print(os);
        return os;
    }

}//end namespace zoo

#endif //ANIMAL_CRTP_HEADER
