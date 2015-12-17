// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 14:14:23 CET
// File:    c++17.cpp

#include <iostream>


template< template<typename> class T > // c++14 requires class here
struct foo {
};

template< template<typename> typename T > // in c++17 class and typename are both fine
struct bar {
};

int main() {
    
    return 0;
}
