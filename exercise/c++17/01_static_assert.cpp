// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:14:23 CET
// File:    c++17.cpp

#include <iostream>


int main() {

    static_assert(false, "Mandatory Message"); // c++14
    static_assert(false); // c++17

    return 0;
}
