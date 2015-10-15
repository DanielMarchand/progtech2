/*******************************************************************************
 *
 * PennaLV Test Main Function (functional test)
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/
#include <zoo/bear.hpp>
#include <zoo/sheep.hpp>
#include <zoo/animal.hpp>
#include <util/random.hpp>
#include <list>

#include <catch.hpp>

TEST_CASE("Functional Test of main", "[mainTest]") {
  using namespace zoo;

  // seed random number generator engine
  util::seed<>(0);

  // set up sheep parameters
  sheep::set_gene_size(32);
  sheep::prop.repr_age = 8;
  sheep::prop.threshold = 3;
  sheep::prop.mut_rate = 2;
  sheep::prop.N_max = 1000;
  sheep::prop.N_init = 1000;
  // set up bear parameters
  bear::set_gene_size(32);
  bear::prop.repr_age = 8;
  bear::prop.threshold = 3;
  bear::prop.mut_rate = 2;
  bear::prop.N_max = 1000;
  bear::prop.N_init = 1000;

  // generate initial population (can hold sheep & bear now)
  std::list<std::shared_ptr<animal>> pop;

  for (uint64_t i = 0; i < sheep::prop.N_init; ++i) {
    std::shared_ptr<animal> s(new sheep(sheep::random_age()));
    pop.push_back(s);
  }

  for (uint64_t i = 0; i < bear::prop.N_init; ++i) {
    std::shared_ptr<animal> b(new bear(bear::random_age()));
    pop.push_back(b);
  }

  // run simulation
  for (uint32_t i = 0; i < 300; ++i) {
    for (auto it = pop.begin(); it != pop.end(); ++it) {
      auto& ap = (*it);

      auto dead = not ap->progress();
      if (dead) {
        it = pop.erase(it);
        --it;
      } else {
        if (ap->adult()) {
          pop.push_front(ap->make_child());
        }
      }
    }
  }

  // Check end of simulation
  INFO("Some of your numerics changed! Might be a bug or not!");
  CHECK(sheep::prop.N_t == 95);
  CHECK(bear::prop.N_t == 55);

}
