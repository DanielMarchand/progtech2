/*******************************************************************************
 *
 * factorial_take1
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <catch.hpp>
#include <mymath/factorial.hpp>

TEST_CASE( "factorial_take1 test-collection", "[factorial]" ) {
    CHECK(factorial_take1(0) == 1);
}


