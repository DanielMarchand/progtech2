// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:38:46 CET
// File:    05_nested_namespace.cpp

#include <iostream>

// c++14
namespace pt2 {
    namespace pennaLV {
        namespace simulation {
            // my code
        }//end namespace simulation
    }//end namespace pennaLV
}//end namespace pt2

// is the same as

// c++17
namespace pt2::pennaLV::simulation {
    // my code
}//end namespace pt2::pennaLV::simulation

int main() {
    
    return 0;
}
