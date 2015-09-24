/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <random>   // c++11
#include <iostream>

int main() {
    // create an engine
    std::mt19937 mt;

    // create four distributions
    std::uniform_int_distribution<int>     uint_d(0, 10);
    std::uniform_real_distribution<double> ureal_d(0., 10.);
    std::normal_distribution<double>       normal_d(0., 4.);
    std::exponential_distribution<double>  exp_d(1.);

    // create random numbers:
    std::cout <<   uint_d(mt) << std::endl;
    std::cout <<  ureal_d(mt) << std::endl;
    std::cout << normal_d(mt) << std::endl;
    std::cout <<    exp_d(mt) << std::endl;
    
    // check the reference for all distr & engines!
    
    return 0;
}
