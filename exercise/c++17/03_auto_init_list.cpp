// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:24:00 CET
// File:    03_auto_init_list.cpp

#include <iostream>

int main() {
    // same
    auto x1 = { 1, 2 }; // decltype(x1) is std::initializer_list<int>
    //auto x2 = { 1, 2.0 }; // error: cannot deduce element type
    auto x4 = { 3 }; // decltype(x4) is std::initializer_list<int>
    
    //c++14
    auto x3{ 1, 2 }; // std::initializer_list<int>
    auto x5{ 3 };    // std::initializer_list<int>
    
    //c++17
    auto x3{ 1, 2 }; // error: not a single element
    auto x5{ 3 };    // decltype(x5) is int
    
    return 0;
}
