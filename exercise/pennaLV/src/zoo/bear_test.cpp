/** ****************************************************************************
 * 
 * \file
 * \brief PennaLV Unit test for zoo::bear class
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright For free use, no rights reserved, with no warranty whatsoever.
 * 
 * \cond IMPLEMENTATION_DETAIL_DOC
 * 
 ******************************************************************************/
 
#include <zoo/bear.hpp>
#include <util/random.hpp>
#include <vector>

#include <catch.hpp>

TEST_CASE("Testing Properties of Bear", "[bearTest]") {
  using namespace zoo;
  util::seed(0);
  // set up bear parameters for common use
  bear::set_gene_size(32);
  bear::prop.repr_age = 8;
  bear::prop.threshold = 3;
  bear::prop.mut_rate = 2;
  
  SECTION("Test Reproduction age") {
    bear test_bear1(1);
    bear test_bear2(2);
    bear test_bear3(3);
    bear test_bear4(4);
    bear::prop.repr_age = 0;
    CHECK(test_bear1.adult() == true);
    CHECK(test_bear2.adult() == true);
    CHECK(test_bear3.adult() == true);
    CHECK(test_bear4.adult() == true);
    bear::prop.repr_age = 3;
    CHECK(test_bear1.adult() == false);
    CHECK(test_bear2.adult() == false);
    CHECK(test_bear3.adult() == true);
    CHECK(test_bear4.adult() == true);
  }
  
  SECTION("Test Max Population") {
    uint64_t N_max = 4;
    uint64_t N_init = 5;
    std::vector<bear> test_sheep_collection;
    for(uint ii=0; ii < N_init; ++ii) {
      test_sheep_collection.push_back(bear(0));
    }
    CHECK(test_sheep_collection[0].progress({0, N_max}, {0, N_max}) == false);
  }
  
  //Create more unit tests. Goal is 100% code coverage!
}
