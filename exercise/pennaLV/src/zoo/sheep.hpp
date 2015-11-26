/** ****************************************************************************
 * 
 * \file
 * \brief Sheep Declaration
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#ifndef ZOO_SHEEP_HEADER
#define ZOO_SHEEP_HEADER

#include <string>

#include "zoo.hpp"
#include "animal_crtp.hpp"

// documented in zoo.hpp
namespace zoo {

    /** \brief Sheep class
     *  \tparam animal_crtp<sheep>  CRTP parent class
     *  \details Sheep are fluffy and don't harm anyone.\n
     *  Their survival characteristics are those of their parent class. In
     *  addition, they have a disappointing culinary interaction() with bears.
     *
     *  This class fulfills the sim::animal_concept.
     */
    class sheep: public animal_crtp<sheep> {
        using super = animal_crtp<sheep>;
        
        public:

        /** \brief Construct a sheep
         *  \param age  of the new sheep in years (default = 0).
         *  \details The constructor will delegate to the parent animal_crtp<sheep>
         *  constructor.
         */
        inline sheep(age_type const & age = 0): super(age) {
        }

        /** \brief Interaction with other animals.
         *  \param N_t  Current population counts of active zoo animals.
         *  \return Probability of survival.
         *  \details The probability to survive interaction with bears corresponds to:\n
         *           `1 - c * # bear / # sheep`\n
         *           With an implementation specific factor c.
         */
        static double interaction(count_array const & N_t);
        
        public:

        /// Name of this particular sort of sheep.
        static const std::string name;
        /// Tag used by zoo::tag::animal_enum for the count array.
        static const tag::animal_enum index = tag::sheep;
    };
    
}//end namespace zoo

#endif // ZOO_SHEEP_HEADER
