/*******************************************************************************
 *
 * Regex code implementation.
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include "reg.hpp"

#include <regex>

std::string dedup_whitespace(std::string const & text) {
    return std::regex_replace(
          text
        , std::regex("\\s+(?=(?:[^\"']*(?:\"[^\"]*\"|'[^']*'))*[^\"']*$)")
        , " ");
}
