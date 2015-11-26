/** ****************************************************************************
 * 
 * \file
 * \brief Bear Declaration
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#ifndef ZOO_BEAR_HEADER
#define ZOO_BEAR_HEADER

#include <string>

#include "animal_crtp.hpp"
#include "zoo.hpp"

// documented in zoo.hpp
namespace zoo {

    /** \brief Bear class
     *  \tparam animal_crtp<bear>  CRTP parent class
     *  \details Bears like to have interaction() with sheep.\n
     *  Their survival characteristics are those of their parent class. In
     *  addition, they die from starvation (sheep scarcity).
     *
     *  This class fulfills the sim::animal_concept.
     */
    class bear: public animal_crtp<bear> {
        using super = animal_crtp<bear>;
        
        public:

        /** \brief Construct a bear
         *  \param age  of the new bear in years (default = 0).
         *  \details The constructor will delegate to the parent animal_crtp<bear>
         *  constructor.
         */
        bear(age_type const & age = 0): super(age) {
        }
        /** \brief Interaction with other animals.
         *  \param N_t  Current population counts of active zoo animals.
         *  \return Probability of survival.
         *  \details The probability to survive interaction with sheep corresponds to:\n
         *           ` # sheep / (2 * # bear)`
         */
        static double interaction(count_array const & N_t);
        
        public:

        /// Name of this particular sort of bear.
        static const std::string name;

        /// Tag used by zoo::tag::animal_enum for the count array.
        static const tag::animal_enum index = tag::bear;

    };
    
}//end namespace zoo

#endif // ZOO_BEAR_HEADER
