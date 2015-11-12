/*******************************************************************************
 * 
 * Thunder Struct Demo Bots
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#ifndef THUNDER_STRUCT_HEADER
#define THUNDER_STRUCT_HEADER

#include <array>
#include <random>

#include "global.hpp"

// not very smart thunder-struct
struct random_bot {
    // the bot needs to have move function
    dir::type move(int const & // field-size
                 , std::array<field_type, dir::N> const & // the six neighbour fields
                 , field_type const & // the field I'm currently on
                 , std::mt19937 & eng // a random engine to only (!)
                 ) {                  // draw numbers from "eng()"
        auto next_move = eng() % dir::N;
        return next_move;
    }
    // and name function
    std::string name() const {
        return "random";
    }
};

// also not the best hunter...
struct dumb_bot {
    dir::type move(int const &
                 , std::array<field_type, dir::N> const &
                 , field_type const &
                 , std::mt19937 &) {
        return dir::right; // always move right
    }
    std::string name() const {
        return "dumb";
    }
};

#endif //THUNDER_STRUCT_HEADER
