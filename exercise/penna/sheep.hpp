/*******************************************************************************
 * 
 * Penna Simulation Code
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#ifndef SHEEP_HEADER
#define SHEEP_HEADER

#include "../extern/include/util/random.hpp"

#include <vector>
#include <ostream>

class sheep {

public:
    sheep(uint const & age = 0): age_(age), bad_genes_(0), gene_(species_gene_size) {
        ++species_N_t;
    }
    sheep(sheep const & rhs): age_(rhs.age_)
                            , bad_genes_(rhs.bad_genes_)
                            , gene_(rhs.gene_) {
        ++species_N_t;
    }
    ~sheep() {
        --species_N_t;
    }
    static void set_gene_size(uint gene_size) {
        species_gene_size = gene_size;
        gene_rng.set_range(0, gene_size - 1);
    }
    sheep make_child(std::string);
    bool adult() {
        return age_ >= species_repr_age;
    }
    static uint random_age() {
        return gene_rng();
    }
    bool progress() {
        bad_genes_ += gene_[age_];
        age_ += 1;

        if(bad_genes_ >= species_threshold) { // darwin selection
            return false;
        }
        if(prob_rng() > (1 - double(species_N_t)/species_N_max)) { // resource selection
            return false;
        }
        if(age_ == species_gene_size) { // too old
            return false;
        }
        return true;
    }
    void name(std::ostream & os) const {
        os << "sheep";
    }
    void print_age(std::ostream & os) const {
        name(os);
        os << ": (age: " << age_ << "): ";
    }
    void print(std::ostream & os) const {
        print_age(os);
        for(uint i = 0; i < gene_.size(); ++i) {
            if(i<age_) { // these blocks just generate colors
                os << "\033[0;";
                if(gene_[i])
                    os << "41m";
                else
                    os << "42m";
            }
            else {
                os << "\033[0;";
                if(gene_[i])
                    os << "31m";
                else
                    os << "32m";
            }
            // acutual print
            os << gene_[i] << "\033[0m";
        }
    }

    static uint species_gene_size;
    static uint species_repr_age;
    static uint species_threshold;
    static uint species_mut_rate;
    static uint species_N_max;
    static uint species_N_t;
    static uint species_N_init;

private:
    uint age_;
    uint bad_genes_;
    std::vector<bool> gene_;

    static util::rng_class<uint> gene_rng;
    static util::rng_class<double> prob_rng;
};


// initialize static variables
uint sheep::species_gene_size;
uint sheep::species_repr_age;
uint sheep::species_threshold;
uint sheep::species_mut_rate;
uint sheep::species_N_max;
uint sheep::species_N_init;
uint sheep::species_N_t;

//gene_rng has to be set again via set_gene_size
util::rng_class<uint> sheep::gene_rng(0, sheep::species_gene_size-1);
util::rng_class<double> sheep::prob_rng(0, 1);

sheep sheep::make_child(std::string owner = "none") {
    sheep child;
    child.gene_ = gene_; //copy gene

    for(uint i = 0; i < species_mut_rate; ++i) { //mutate some gene
        auto pos = gene_rng();
        child.gene_[pos] = !child.gene_[pos]; //flip random gene
    }
    return child;
    (void)owner; //prevent unused variable message :P
}

std::ostream & operator<<(std::ostream & os, sheep const & arg) {
    arg.print(os);
    return os;
}

#endif //SHEEP_HEADER
