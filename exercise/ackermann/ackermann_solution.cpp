/** ****************************************************************************
 * 
 * \file
 * \brief Ackermann Example Solution
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * 
 ******************************************************************************/
 
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

// link against libboost_serialization

#include <map>
#include <fstream>
#include <iostream>

class {
public:
    double operator()(double const & m, double const & n) {
        std::pair<int, int> p(m, n);
        
        if(cache_.count(p))
            return cache_.at(p);
        
        double res = 0;
        if(m == 0)
            res = n+1;
        else if(n == 0)
            res = (*this)(m-1, 1);
        else
            res = (*this)(m-1, (*this)(m, n-1));
        
        cache_[p] = res;
        return res;
    }
    template<typename Archive>
    void serialize(Archive & ar, int const & version) {
        ar & cache_;
    }
private:
    std::map<std::pair<int, int>, double> cache_;
} ackerman;

int main() {
    std::string fname = "ackerman_cache";
    
    // read from archive if found
    std::ifstream ifs(fname);
    if(ifs.is_open()) {
        boost::archive::binary_iarchive iar(ifs);
        iar >> ackerman;
    }
    ifs.close();
    
    // calculate some ackerman-values (don't even try ackerman(4, >2))
    std::cout << ackerman(1, 1) << std::endl;
    std::cout << ackerman(3, 14) << std::endl;
    
    // write to archive
    std::ofstream ofs(fname);
    boost::archive::binary_oarchive oar(ofs);
    oar << ackerman;
    ofs.close();
    
    return 0;
}
