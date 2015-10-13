/*******************************************************************************
 *
 * Function to determine if integer is prime
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "isPrime.hpp"

bool IsPrime(int n) {
  if (n <= 1) return false;
  if (n % 2 == 0) return false;
  for (int ii = 3; ; ii += 2) {
    if (ii >= n / ii) break;  // Only try up to square root of n
    if (n % ii == 0) return false;
  }
  return true;
}
