// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    16.12.2015 22:07:33 CET
// File:    09_concept_lite.cpp

#include <iostream>

//======================================
concept LessThanComparable<typename T> { // concept keyword
    bool operator<(T, T);
}

template<LessThanComparable T>
const T& min(const T &x, const T &y) {
    return (y < x) ? y : x;
}

//======================================
auto concept Convertible<typename T, typename U> {
    operator U(const T&);
}

template<typename U, typename T> requires Convertible<T, U> // here we need require
U convert(const T& t) {
    return t;
}

//======================================
concept InputIterator<typename Iter, typename Value> { 
    typename value_type;    // typedefs can also be checked for
    requires Regular<Iter>; // requires keyword 
    Value operator*(const Iter&);
    Iter& operator++(Iter&);
    Iter operator++(Iter&, int);
}

int main() {
    
    return 0;
}
