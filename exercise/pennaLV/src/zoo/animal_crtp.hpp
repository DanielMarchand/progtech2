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
#include "animal.hpp"
#include <util/random.hpp>

#include <memory>

namespace zoo {
    template<typename T>
    class animal_crtp: public animal {
        using super = animal;
        public:
        // structors
        animal_crtp(age_type const & age = 0): super(age, prop.gene_size) {}
        // can be ommited here since the base has virtual dtor,
        // thus this dtor will be generated virtual
        // virtual ~animal_crtp() {}

        // modifying methods
        bool progress(sim::count_array const & N_max
                    , sim::count_array const & N_t) override {
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
        inline bool adult() const override {
            return age_ >= prop.repr_age;
        }
        inline tag::zoo_enum index() const override {
            return T::index;
        }
        std::shared_ptr<animal> make_child() const override {
            std::shared_ptr<animal_crtp> child(new animal_crtp());
            child->gene_ = gene_; // copy gene

            for(mut_type i = 0; i < prop.mut_rate; ++i) { // mutate some gene
                auto pos = gene_rng();
                child->gene_[pos] = !child->gene_[pos]; // flip random gene
            }
            return child;
        }

        inline std::string name() const override {
            return T::name;
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
        private:
        static util::rng_class<age_type> gene_rng;
        static util::rng_class<double> prob_rng;
    };

    // static members
    template<typename T>
    species_properties animal_crtp<T>::prop;

    // gene_rng has to be set again via set_gene_size
    template<typename T>
    util::rng_class<age_type> animal_crtp<T>::gene_rng(0, animal_crtp<T>::prop.gene_size - 1);

    template<typename T>
    util::rng_class<double> animal_crtp<T>::prob_rng(0, 1);

}//end namespace zoo

#endif //ANIMAL_CRTP_HEADER
