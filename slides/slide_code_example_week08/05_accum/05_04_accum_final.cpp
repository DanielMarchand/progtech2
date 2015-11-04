// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:02:24 CET
// File:    accum_demo.cpp

//=================== include ===================
#include "../presentation.hpp"
// header not provided bc parts are an exercise
#include "accumulator/accum.hpp"

//=================== main ===================
int main() {
    
    // headers not provided bc parts are an exercise
    using acc_type = accum<int, tag::count
                              , tag::error
                              , tag::ema<4>
                              , tag::min
                              , tag::max
                              >;

    acc_type acc;
    
    acc << 1 << 2 << 3 << 4;
    
    CW_NORMAL(
    PNW_GREEN(acc.count())
    PNW_YELLOW(acc.mean())
    PNW_YELLOW(acc.std())
    PNW_RED(acc.min())
    PNW_RED(acc.max())
    PNW_BLUE(acc.ema())
    )
    
    PNWW_GREEN(sizeof(acc_type))
    
    return 0;
}
