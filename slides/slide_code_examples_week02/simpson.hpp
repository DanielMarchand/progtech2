/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

// I ommit "const &" and further technical details for readibility

#ifndef SIMPSON_HEADER
#define SIMPSON_HEADER

#include <functional> // std::function

double simpson(std::function<double(double)> f, double a, double b, unsigned int N) {
    return 2; // implement if you want :)
}

#endif //SIMPSON_HEADER
