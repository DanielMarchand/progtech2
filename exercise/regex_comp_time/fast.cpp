/*******************************************************************************
 *
 * This code compiles quickly after edits.
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include "reg.hpp"
#include <iostream>

int main() {

    std::string text = "That is    a  string 'with  too  much' whitespace.";
    std::cout << text << std::endl;
    std::cout << dedup_whitespace(text) << std::endl;

    return 0;

}
