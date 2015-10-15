/*******************************************************************************
 *
 * factorial_take2
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <catch.hpp>
#include <mymath/factorial.hpp>
#include <stdexcept>

TEST_CASE( "factorial_take2 test-collection", "[factorial]" ) {
    CHECK_THROWS_AS(factorial_take2(13), std::logic_error);
    CHECK_NOTHROW(factorial_take2(12));
}


