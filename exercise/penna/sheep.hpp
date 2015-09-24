/*******************************************************************************
 *
 * Sheep Declaration
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
    struct species_properties {
        uint gene_size;
        uint repr_age;
        uint threshold;
        uint mut_rate;
        uint N_max;
        uint N_init;
        uint N_t;
    };

    public:
    // structors & assignment
    sheep(uint const & age = 0): age_(age) // dual-interface
                                      , bad_genes_(0)
                                      , gene_(prop.gene_size) {
        ++prop.N_t;
    }
    inline sheep(sheep const & rhs): age_(rhs.age_)
                                   , bad_genes_(rhs.bad_genes_)
                                   , gene_(rhs.gene_) {
        ++prop.N_t;
    }

    inline ~sheep() {
        --prop.N_t;
    }
    
    // modifying methods
    bool progress();

    // const methods
    inline bool adult() const {
        return age_ >= prop.repr_age;
    }
    sheep make_child() const;
    inline std::string name() const {
        return "sheep";
    }
    void print(std::ostream & os) const;

    // static methods
    inline static uint random_age() {
        return gene_rng();
    }
    
    static void set_gene_size(uint const & gene_size);

    // members
    private:
    uint age_;
    uint bad_genes_;
    std::vector<bool> gene_;

    // static members
    public:
    static species_properties prop;
    private:
    static util::rng_class<uint> gene_rng;
    static util::rng_class<double> prob_rng;
};

// free functions
std::ostream & operator<<(std::ostream & os, sheep const & arg);

#endif //SHEEP_HEADER
