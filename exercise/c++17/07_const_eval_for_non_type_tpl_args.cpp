// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:52:46 CET
// File:    07_const_eval_for_non_type_tpl_args.cpp

#include <iostream>

struct my_class {
    constexpr my_class(int v) : value(v) { }
    int value;
};

template<my_class m>
struct X {
    int array[m.value];
};

int main() {

    // c++17
    X<my_class(42)> x;
    
    (void)x; // to avoid unused variable
    return 0;
}
