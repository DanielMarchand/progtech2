/** ****************************************************************************
 * 
 * \file
 * \brief Ackermann Example
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * 
 ******************************************************************************/

// get the propper boost/archive and boost/serialization includes

#include <iostream>

class {
public:
    double operator()(double const & m, double const & n) {
        if(m == 0)
            return n+1;
        else if(n == 0)
            return (*this)(m-1, 1);
        else
            return (*this)(m-1, (*this)(m, n-1));
    }
private:
} ackerman;

int main() {
    
    // read from archive if found
    // input_archive >> ackerman;
    
    // calculate some ackerman-values (don't even try ackerman(4, >2))
    std::cout << ackerman(1, 1) << std::endl;
    std::cout << ackerman(3, 14) << std::endl;
    
    // write to archive
    // output_archive << ackerman;
    
    return 0;
}
