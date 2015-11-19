/** ****************************************************************************
 * 
 * \file
 * \brief Zoo header
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright For free use, no rights reserved, with no warranty whatsoever.
 * \details This file hold the animal enumaration tags for.
 * 
 ******************************************************************************/

#ifndef ZOO_ZOO_HEADER
#define ZOO_ZOO_HEADER

#include <cstdint>

/// \brief Animal library namespace
namespace zoo {
    /// \brief Animal library tag variables
    namespace tag {
        using type = uint8_t;     ///< &nbsp;
        /** \brief Give each animal a tag through enumeration
         *  \details The last element implicitly sets the animal count.
         */
        enum animal_enum: type {
              sheep
            , bear
            , N_animal
        };
        
    } // namespace tag
} // namespace zoo

#endif // ZOO_ZOO_HEADER
