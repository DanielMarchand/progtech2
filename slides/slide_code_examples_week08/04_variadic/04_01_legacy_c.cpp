// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 11:27:56 CET
// File:    04_01_legacy_c.cpp

//=================== includes ===================
#include "../presentation.hpp"
#include <stdarg.h> // used for variadic functions


//=================== type-unsafe mean ===================
double mean(int const & N, ...) {
    va_list ap;      // the argument pack
    va_start(ap, N); // initializes argument pack

    double sum = 0;
    
    for(int i = 0; i < N; ++i) {
        double val = va_arg(ap, double); // hope and pray it's a double
        //~ PNW_MAGENTA(val)
        sum += val;
    }
    
    va_end(ap); // clean-up
    
    return sum / N;
}

//=================== main ===================
int main() {
    P_YELLOW("variadic functions (since c)")
    
    // best knows variadic function
    CNWW_YELLOW(printf("%s %s! %f\n", "Hello", "World", 1.1))
    
    // works for doubles (result: 2)
    PNW_GREEN(mean(5, 0., 1., 2., 3., 4.))
    
    // fails for mixed (result: pretty random, mostly nan)
    PNW_RED(mean(5, 0, 1., 2, 3., 4))
    
    return 0;
}
