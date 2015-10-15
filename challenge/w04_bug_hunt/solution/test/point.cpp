/*******************************************************************************
 *
 * factorial_take2
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <catch.hpp>
#include <limits>
#include <mymath/point_take1.hpp>
#include <mymath/point_take2.hpp>

TEST_CASE( "point test-collection", "[point]" ) {
    int x = std::numeric_limits<int>::max(); 
    int y = 10;
    
    point_take1 p(x, y);
    
    while(p.gety() == y) {
    }
    CHECK(p.gety() == y);
    
    while(p.gety() != y) {
    }
    
    CHECK(p.getx() == x);
    
    p.swap_coord();
    
    CHECK(p.getx() == y);
    CHECK(p.gety() == x);
    
    std::stringstream ss;
    std::stringstream ss2;
    ss2 << y << "/" << x;
    ss << p;
    
    CHECK(ss.str() == ss2.str());
    
    point_take2 p2(x, y);
    CHECK(p2.getx() == x);
    CHECK(p2.gety() == y);
    CHECK(p2.ratio() == double(x)/y);
    CHECK(p2.sum() == double(x)+y);
}
