// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.10.2015 23:31:33 CEST
// File:    measure_perf.cpp

#include <list>
#include <vector>
#include <iostream>

#include "../../exercise/extern/include/util/profiler.hpp"

int main(int argc, char* argv[]) {
    
    MIB_START("main")
    std::vector<int> vec;
    std::list<int> li;
    uint N = 100000;
    
    MIB_START("pushback")
    for(uint i = 0; i < N; ++i) {
        MIB_START("vec::pb")
        vec.push_back(i);
        MIB_NEXT("li::pb")
        li.push_back(i);
        MIB_STOP("li::pb")
    }
    
    MIB_NEXT("popfront")
    for(uint i = 0; i < N; ++i) {
        MIB_START("vec::pf")
        vec.erase(vec.begin());
        MIB_NEXT("li::pf")
        li.erase(li.begin());
        MIB_STOP("li::pf")
    }
    MIB_STOP("popfront")
    
    MIB_STOP("main")
    
    MIB_PRINT("cycle")
    MIB_PRINT("nsec")
    
    std::string name = "list_vector_comparison.txt";
    
    if(argc > 1)
        name = argv[1];
    
    MIB_SAVE("cycle", name)
    
    return 0;
}
