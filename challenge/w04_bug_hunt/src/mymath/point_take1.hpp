/*******************************************************************************
 *
 * Point Take 1 Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <cstdint>
#include <iostream>

// a point that stores the coordinates x and y
class point_take1 {
public:
    // structors
    
    // precondition:  none
    // postcondition: initializes a point to represent the coordinates (x/y)
    point_take1(int x, int y);
    // modifying methods
    
    // precondition:  none
    // postcondition: swappes the coordinates from (x/y) to (y/x)
    void swap_coord();
    
    // const methods
    
    // precondition:  none
    // postcondition: returns the value of the coordinate x
    //                does not change the coordinates
    int const & getx();
    
    // precondition:  none
    // postcondition: returns the value of the coordinate y
    //                does not change the coordinates
    int const & gety();
    
    friend std::ostream & operator<<(std::ostream &, point_take1 const &);
private:
    int l1I_;
    int Il1_;
    int lI1_;
};

// precondition:  none
// postcondition: prints the coordinates "x/y" e.g. "10/5" if x = 10 and y = 5
//                does not change the coordinates
std::ostream & operator<<(std::ostream &, point_take1 const &);
