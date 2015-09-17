/*******************************************************************************
 * 
 * This code compiles slowly after edits.
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>
#include <regex>

// This function removes excessive whitespace that is not encased in quotes.
std::string dedup_whitespace(std::string const & text) {
    return std::regex_replace(
          text
        , std::regex("\\s+(?=(?:[^\"']*(?:\"[^\"]*\"|'[^']*'))*[^\"']*$)")
        , " ");
}

int main() {

    std::string text = "That is    a  string 'with  too  much' whitespace.";
    std::cout << text << std::endl;
    std::cout << dedup_whitespace(text) << std::endl;

    return 0;

}
