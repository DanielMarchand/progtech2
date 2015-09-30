#include <tutorial_config.hpp>

#ifdef USE_MYSQRT
    #include <my_sqrt.hpp>
#else
    #include <cmath>
#endif

int main() {
    double a = 9;
    
    #ifdef USE_MYSQRT
        if(my_sqrt(a) != 1111)
            return 1;
    #else
        if(std::sqrt(a) != 3)
            return 1;
    #endif
    
    return 0;
}
