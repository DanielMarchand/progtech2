/*******************************************************************************
 *
 * Animal Base Class Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "animal.hpp"

namespace zoo {

    // structors
    animal::~animal() {} // since the dtor is called implicitly,
                         // we need to provide it (even if pure virtual)

    // const methods
    void animal::print(std::ostream & os) const {
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

    // free functions
    std::ostream & operator<<(std::ostream & os, animal const & arg) {
        arg.print(os);
        return os;
    }

}//end namespace zoo
