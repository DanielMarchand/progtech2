// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    02.11.2015 11:02:38 CET
// File:    accum_base.hpp

#ifndef ACCUM_BASE_HEADER
#define ACCUM_BASE_HEADER

template<typename T>
class accum_base {
public:
    // modifying methods
    accum_base & operator<<(T const &) { return (*this); }
    void clear() {}
};

#endif //ACCUM_BASE_HEADER
