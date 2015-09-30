/*******************************************************************************
 *
 * Sheep Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef SHEEP_HEADER
#define SHEEP_HEADER

#include <vector>
#include <ostream>

#include "animal.hpp"
#include "util/random.hpp"

namespace zoo {

    class sheep: public animal {
        using super = animal;
        
        public:
        // structors & assignment
        inline sheep(age_type const & age = 0): super(age, prop.gene_size) {
            ++prop.N_t;
        }
        inline sheep(sheep const & rhs): super(rhs) {
            ++prop.N_t;
        }
        inline ~sheep() {
            --prop.N_t;
        }
        
        // modifying methods
        bool progress() override;

        // const methods
        inline bool adult() const override {
            return age_ >= prop.repr_age;
        }
        sheep * make_child() const override; // will still override animal * make_child()
        inline std::string name() const override {
            return "sheep";
        }

        // static methods
        inline static age_type random_age() {
            return gene_rng();
        }
        
        static void set_gene_size(age_type const & gene_size);

        // static members
        public:
        static species_properties prop;
        private:
        static util::rng_class<uint> gene_rng;
        static util::rng_class<double> prob_rng;
    };
    
}//end namespace zoo

#endif //SHEEP_HEADER
