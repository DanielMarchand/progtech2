// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 14:36:22 CET
// File:    03_03_compile_time_prime.cpp

//=================== no macros ===================
//=================== no includes ===================

//=================== meta templates ===================

//=================== main ===================
void no_main() { //;-) 
    //~ int const n = 10;
    int const n = 100;
    
    //not optimal since it goes from 2 to n instead of going from n to 0
    
    // not provided bc it's a challenge :)
    
    result_type::foo; //for a compiletime error
}
