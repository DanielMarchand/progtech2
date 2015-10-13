/*******************************************************************************
 *
 * Unit tests for IsPrime using CATCH
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "isPrime.hpp"
#include <catch.hpp>
#include <vector>

TEST_CASE( "IsPrimeTest Trivial Cases", "[isPrimeTest]" ) {
  CHECK(IsPrime(0) == false);
  CHECK(IsPrime(1) == false);
  CHECK(IsPrime(2) == true);
  CHECK(IsPrime(3) == true);
}

TEST_CASE( "IsPrimeTest Negative Integers", "[isPrimeTest]" ) {
  CHECK(IsPrime(-1) == false);
  CHECK(IsPrime(-2) == false);
}

/*TEST_CASE("IsPrimeTest Positive Integers", "[isPrimeTest]") {
  std::vector<int> non_primes = {0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20};
  std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};

  SECTION("Testing small non-primes") {
    for (const auto& non_prime : non_primes) {
      //INFO("Testing non_prime = " << non_prime);
      CHECK(IsPrime(non_prime) == false);
    }
    non_primes = {}; // Does not have effect outside the scope of this Section
    primes = {};
    REQUIRE(non_primes.size() == 0);
    REQUIRE(primes.size() == 0);
  }

  SECTION("Testing small primes") {
    REQUIRE(non_primes.size() == 13); // See non_primes = {} does not have effect here
    REQUIRE(primes.size() == 8);
    for (const auto& prime : primes) {
      CHECK(IsPrime(prime) == true);
    }
  }
}*/

