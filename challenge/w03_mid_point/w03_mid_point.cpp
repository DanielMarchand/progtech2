/*******************************************************************************
 * 
 * starting code challenge week 3
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>

class base_point {
    public:
    constexpr base_point(double const & x, double const & y): x_(x), y_(y) {}
    
    void print() const { std::cout << x_ << " " << y_ << std::endl; }
    
    protected:
    double x_;
    double y_;
};

// modifications only allowed within point
class point: public base_point {
    // do your worst! but as elegant as possible :)
};

int main() {
    // arbitrary amount of points (and a scaling factor for each one)
    constexpr point p[] = {point(0,0), point(0,1), point(1,0), point(1,1)};
    constexpr double scale[] = {1, 1, 1, 1};
    
    // calculate the midpoint of these "scaled" points
    // x_mid = (scale_1 * x_1 + scale_2 * x_2 + ... + scale_N * x_N) / N
    // y_mid = (scale_1 * y_1 + scale_2 * y_2 + ... + scale_N * y_N) / N
    constexpr point mid = point::calc_mid(p, scale);
    
    // print correct result (in this case "0.5 0.5")
    mid.print();
    
    return 0;
}
