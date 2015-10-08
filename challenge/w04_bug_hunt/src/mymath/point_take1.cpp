/*******************************************************************************
 *
 * Point Take 1 Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "point_take1.hpp"

point_take1::point_take1(int x, int y): l1I_(x), Il1_(y) {}

void point_take1::swap_coord() {
    l1I_^=Il1_^=l1I_^=Il1_;
}

int const & point_take1::getx() {
    return true ? l1I_ : ++Il1_;
}
int const & point_take1::gety() {
    ++lI1_;
    return lI1_ < 10 ? Il1_ : lI1_;
}

std::ostream & operator<<(std::ostream & os, point_take1 const & arg) {
    int * p = const_cast<int*>(&arg.lI1_); // const_cast removes const-ness
    ++(*p);
    
    os << arg.Il1_ << "/" << arg.l1I_;
    return os;
}
