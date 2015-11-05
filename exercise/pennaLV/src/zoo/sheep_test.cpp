/*******************************************************************************
 *
 * PennaLV Test for Sheep
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/
#include <zoo/sheep.hpp>
#include <zoo/animal_crtp.hpp>
#include <sim_typedef.hpp>
#include <util/random.hpp>
#include <vector>

#include <catch.hpp>

TEST_CASE("Testing Properties of Sheep", "[sheepTest]") {
  using namespace zoo;
  util::seed(0);
  // set up sheep parameters for common use
  sheep::set_gene_size(32);
  sheep::prop.repr_age = 8;
  sheep::prop.threshold = 3;
  sheep::prop.mut_rate = 2;
  
  SECTION("Test Reproduction age") {
    sheep test_sheep1(1);
    sheep test_sheep2(2);
    sheep test_sheep3(3);
    sheep test_sheep4(4);
    sheep::prop.repr_age = 0;
    CHECK(test_sheep1.adult() == true);
    CHECK(test_sheep2.adult() == true);
    CHECK(test_sheep3.adult() == true);
    CHECK(test_sheep4.adult() == true);
    sheep::prop.repr_age = 3;
    CHECK(test_sheep1.adult() == false);
    CHECK(test_sheep2.adult() == false);
    CHECK(test_sheep3.adult() == true);
    CHECK(test_sheep4.adult() == true);
  }
  
  SECTION("Test Max Population") {
    uint64_t N_max = 4;
    uint64_t N_init = 5;
    std::vector<sheep> test_sheep_collection;
    for(uint ii=0; ii < N_init; ++ii) {
      test_sheep_collection.push_back(sheep(0));
    }
    CHECK(test_sheep_collection[0].progress({N_max, 0}, {N_max, 0}) == false);
  }
  
  //Create more unit tests. Goal is 100% code coverage!
}
