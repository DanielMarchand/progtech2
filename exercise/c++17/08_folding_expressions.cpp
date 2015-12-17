// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 21:49:23 CET
// File:    08_folding_expressions.cpp

#include <iostream>

// c++14
double accumulate() {
    return 0;
}
template<typename T, typename... Args>
double accumulate(T const & val, Args const &... args) {
    return val + accumulate(args...);
}

template<typename... Args>
double mean14(Args const &... args) {
    return accumulate(args...) / sizeof...(args);
}

// c++17
template<typename... Args>
double mean17(Args const &... args) {
    return (args + ...) / sizeof...(args); // unary left fold
    // (args OP ...) ==> ((args0 OP args1) OP args2 ) OP ...
}

//=================== main ===================
int main() {
    /*legal folding ops
    
    +  -  *  /  %  ^  &  |  =  <  >  <<  >>
    +=  -=  *=  /=  %=  ^=  &=  |=  <<=  >>=
    ==  !=  <=  >=  &&  ||  ,  .*  ->*
    
    */
    std::cout << mean14(0, 1., 2, 3.4, 4) << std::endl;
    std::cout << mean17(0, 1., 2, 3.4, 4) << std::endl;
}
