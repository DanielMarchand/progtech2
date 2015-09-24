/*******************************************************************************
 *
 * Sheep Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "sheep.hpp"

// structors
// all inline for speed

// modifying methods
bool sheep::progress() {
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
    return true;
}

sheep sheep::make_child() const {
    sheep child;
    child.gene_ = gene_; // copy gene

    for(uint i = 0; i < prop.mut_rate; ++i) { // mutate some gene
        auto pos = gene_rng();
        child.gene_[pos] = !child.gene_[pos]; // flip random gene
    }
    return child;
}

void sheep::print(std::ostream & os) const {
    os << name() << ": (age: " << age_ << "): ";
    for(uint i = 0; i < gene_.size(); ++i) {
        os << "\033[0;";
        if(i<age_) { // these blocks just generate colors
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
void sheep::set_gene_size(uint const & gene_size) {
    prop.gene_size = gene_size;
    gene_rng.set_range(0, prop.gene_size - 1);
}

// static membes
sheep::species_properties sheep::prop;

// gene_rng has to be set again via set_gene_size
util::rng_class<uint> sheep::gene_rng(0, sheep::prop.gene_size - 1);
util::rng_class<double> sheep::prob_rng(0, 1);

// free functions
std::ostream & operator<<(std::ostream & os, sheep const & arg) {
    arg.print(os);
    return os;
}
