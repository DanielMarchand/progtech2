/*******************************************************************************
 *
 * PennaLV Test Bear
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/
#include <zoo/bear.hpp>
#include <zoo/animal.hpp>
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
  bear::prop.N_max = 5;
  bear::prop.N_init = 5;
  
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
    bear::prop.N_max = 4;
    bear::prop.N_init = 5;
    std::vector<bear> test_bear_collection;
    for(uint ii=0; ii< bear::prop.N_init; ++ii) {
      test_bear_collection.push_back(bear(0));
    }
    CHECK(test_bear_collection[0].progress() == false);
  }
  
  //Create more unit tests. Goal is 100% code coverage!
}
