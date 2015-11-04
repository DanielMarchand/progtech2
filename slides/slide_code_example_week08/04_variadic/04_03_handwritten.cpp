// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 09:05:59 CET
// File:    04_03_handwritten.cpp

//=================== include ===================
#include "../presentation.hpp"

//=================== accumulate ===================
// handwritten mean
double mean_ddddd(double const & val0
                             , double const & val1
                             , double const & val2
                             , double const & val3
                             , double const & val4
                             ) {
    P_SIG()
    PN_MAGENTA(val0)
    PN_MAGENTA(val1)
    PN_MAGENTA(val2)
    PN_MAGENTA(val3)
    PN_MAGENTA(val4)
    return (val0 + val1 + val2 + val3 + val4) / 5;
}

double mean_ididi(int    const & val0
                , double const & val1
                , int    const & val2
                , double const & val3
                , int    const & val4
                ) {
    P_SIG()
    PN_MAGENTA(val0)
    PN_MAGENTA(val1)
    PN_MAGENTA(val2)
    PN_MAGENTA(val3)
    PN_MAGENTA(val4)
    return (val0 + val1 + val2 + val3 + val4) / 5;
}

//=================== main ===================
int main() {
    P_YELLOW("handwritten mean")
    
    PNW_GREEN(mean_ddddd(0., 1., 2., 3., 4.))
    
    PNW_RED(mean_ididi(0, 1., 2, 3., 4))
    
    return 0;
}
