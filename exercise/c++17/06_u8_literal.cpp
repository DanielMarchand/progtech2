// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:44:08 CET
// File:    06_u8_literal.cpp

#include <iostream>
#include "/home/msk/Desktop/PT2_live/lecture/exercise/extern/include/util/print_type.hpp"

int main() {
    
    // c++14
    PRINT_TYPE_OF('c')  // char
    PRINT_TYPE_OF(L'c') // wchar_t
    PRINT_TYPE_OF(u'c') // char16_t
    PRINT_TYPE_OF(U'c') // char32_t
    
    //c++17
    PRINT_TYPE_OF(u8'c') // char
    
    return 0;
}
