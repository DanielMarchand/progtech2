/*******************************************************************************
 *
 * Bear Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "bear.hpp"
#include "sheep.hpp"

namespace zoo {
    
    // structors
    // all inline for speed

    // modifying methods
    bool bear::progress() {
        bad_genes_ += gene_[age_];
        age_ += 1;

        if(bad_genes_ >= prop.threshold) { // darwin selection
            return false;
        }
        if(prob_rng() > (1 - double(prop.N_t) / prop.N_max)) { // resource selection
            return false;
        }
        if(age_ == prop.gene_size) { // too old
            return false;
        }
        if(prob_rng() > sheep::prop.N_t / double(2 * bear::prop.N_t)) {
            return false;
        }
        
        return true;
    }

    bear * bear::make_child() const {
        bear * child = new bear();
        child->gene_ = gene_; // copy gene

        for(mut_type i = 0; i < prop.mut_rate; ++i) { // mutate some gene
            auto pos = gene_rng();
            child->gene_[pos] = !child->gene_[pos]; // flip random gene
        }
        return child;
    }

    // static methods
    void bear::set_gene_size(age_type const & gene_size) {
        prop.gene_size = gene_size;
        gene_rng.set_range(0, prop.gene_size - 1);
    }

    // static membes
    species_properties bear::prop;

    // gene_rng has to be set again via set_gene_size
    util::rng_class<age_type> bear::gene_rng(0, bear::prop.gene_size - 1);
    util::rng_class<double> bear::prob_rng(0, 1);

}//end namespace zoo
