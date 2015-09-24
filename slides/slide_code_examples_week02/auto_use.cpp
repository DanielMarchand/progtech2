/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <map>

int main() {
    
    
    // bad
    std::vector<double> vec;
    for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        
    }
    
    // new (but not best c++11 solution)
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        
    }
    
    // bad
    std::map<std::string, double> mymap;
    mymap["a"] = 1;
    std::pair<std::string, double> p = *mymap.begin();
    std::pair<std::string, float> p_oops = *mymap.begin();
    
    // better
    typedef std::map<std::string, double> mymap_t;
    mymap_t mymap2;
    mymap2["a"] = 1;
    mymap_t::value_type p2 = *mymap2.begin();
    
    // best
    auto p3 = *mymap.begin();
    
    
    // type-shortcuts
    uint size = vec.size(); //hmmm, its probably an uint?! good enough...
    
    // correct, but very few do this:
    std::vector<double>::size_type size2 = vec.size();
    
    // solves the problem
    auto size3 = vec.size();
    
    return 0;
}
