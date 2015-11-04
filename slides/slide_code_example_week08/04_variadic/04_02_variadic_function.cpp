// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 13:17:08 CET
// File:    04_02_variadic_function.cpp

/*
inline matters here
*/

//=================== include ===================
#include "../presentation.hpp"

//=================== accumulate ===================
// stop the recursion
double accumulate() {
    //~ P_SIG()
    //~ P_BLUE("end")
    return 0;
}

// accumulate
// Args and args is convention, could be any name
// typename... specifies a variadic template type (must be at the end)
// we specify the pattern "Args const &" and the use ...
// to use this pattern for all types in the argument-pack
template<typename T, typename... Args>
double accumulate(T const & val, Args const &... args) {
    //~ P_SIG()
    //~ PN_MAGENTA(val)
    return val + accumulate(args...);
}

//=================== type-safe mean ===================
// Args and args is convention, could be any name
template<typename... Args>
double mean(Args const &... args) {
    // sizeof...(args) or sizeof...(Args) returns how many 
    // argument are found in the argument-pack
    //~ PNW_BLUE(sizeof...(args))
    //~ PNW_BLUE(TYPE(Args...))
    return accumulate(args...) / sizeof...(args);
}

//=================== main ===================
int main() {
    P_YELLOW("variadic template (since c++11)")
    
    // now also a variadic function template in c++11
    CNWW_YELLOW(std::printf("%s %s! %f\n", "Hello", "World", 1.1))
    
    // doesn't need the count anymore (result: 2)
    PNW_GREEN(mean(0., 1., 2., 3., 4.))
    
    // works also for mixed (result: 2)
    PNW_RED(mean(0, 1., 2, 3., 4))
    
    return 0;
}
