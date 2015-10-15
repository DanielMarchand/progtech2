/*******************************************************************************
 *
 * Animal Base Class Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef ANIMAL_HEADER
#define ANIMAL_HEADER

#include <memory>
#include <vector>
#include <iostream>

namespace zoo {
    // typedefs (we still call them typedefs even if we dont use typedef)
    using age_type = uint32_t;
    using count_type = uint64_t;
    using mut_type = uint32_t;

    // define this struct only once 
    // (could also be in animal... / not in bear AND sheep !)
    struct species_properties {
        age_type gene_size; // not optimal, but max_age and gene_size are connected
        age_type repr_age;
        mut_type threshold;
        mut_type mut_rate;
        count_type N_max;
        count_type N_init;
        count_type N_t;
    };

    class animal {
    public:
        animal();
        virtual ~animal() = 0; // virtual here is important!
        
        // structors & assignment
        animal(age_type const & age
                    , age_type const & gene_size): age_(age)
                                                 , bad_genes_(0)
                                                 , gene_(gene_size) {}
        
        animal(animal const & rhs) = default; // for clarity
        
        // modifying methods
        virtual bool progress() = 0;

        // const methods
        virtual bool adult() const = 0;
        virtual std::shared_ptr<animal> make_child() const = 0;
        virtual std::string name() const = 0;
        virtual void print(std::ostream & os) const;

        // members
        protected: // since derived class need access
        age_type age_;
        mut_type bad_genes_;
        std::vector<bool> gene_;
    };

    std::ostream & operator<<(std::ostream & os, animal const & arg);

}//end namespace zoo

#endif //ANIMAL_HEADER
