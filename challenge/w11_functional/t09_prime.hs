-- Test if a number is prime
-- Programming Techniques for Scientific Simulations 2, ETH Zürich, 2015
-- Licensed under the Apache License (http://www.apache.org/licenses/LICENSE-2.0)
--
-- compile with
--   ghc -outputdir ghc.tmp --make t09_prime.hs

isPrime k = null [ x | x <- [2..k - 1], k `mod`x  == 0]

main = do
  print(isPrime(7))
  print(isPrime(8))
