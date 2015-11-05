// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 08:19:06 CET
// File:    01_02_main.cpp


//=================== include ===================
#include <iostream>
#include <iterator>
#include "01_02_array.hpp"
#include "../../presentation.hpp"

//=================== main ===================
int main() {
    
    // create an array
    pt2_array<int, 5> array;
    
    // and fill it
    for(uint i = 0; i < array.size(); ++i)
        array[i] = i;
    
    // print the array
    CNWW_GREEN(
    for(auto const & e: array) {
        PN_NORMAL(e)
    }
    )
    
    // advance the begin by 5
    auto it = array.begin();
    CNW_YELLOW(std::advance(it, 5))
    
    // and the print the array in reverse
    NEW_LINE()
    CNW_RED(
    do {
        --it;
        PN_NORMAL(*it);
    } while(it != array.begin());
    )
    std::cout << std::endl;
    
    PW_YELLOW("tags can be used instead of bools to categorize")

return 0;
}
