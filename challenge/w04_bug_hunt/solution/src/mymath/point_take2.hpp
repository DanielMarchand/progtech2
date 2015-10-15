/*******************************************************************************
 *
 * Point Take 2 Declaration
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <cstdint>
#include <iostream>

// a point that stores the coordinates x and y
class point_take2 {
public:
    // structors
    
    // precondition:  none
    // postcondition: initializes a point to represent the coordinates (x/y)
    point_take2(int x, int y);
    // modifying methods
    
    // precondition:  none
    // postcondition: swappes the coordinates from (x/y) to (y/x)
    void swap_coord();
    
    // const methods
    
    // precondition:  none
    // postcondition: returns the ratio of x/y with double precision
    //                does not change the coordinates
    double ratio() const;
    
    // precondition:  none
    // postcondition: returns the sum of x + y with double precision
    //                does not change the coordinates
    double sum() const;
    
    // precondition:  none
    // postcondition: returns the value of the coordinate x
    //                does not change the coordinates
    int getx() const;
    
    // precondition:  none
    // postcondition: returns the value of the coordinate y
    //                does not change the coordinates
    int gety() const;
private:
    int x_;
    int xy_;
};
