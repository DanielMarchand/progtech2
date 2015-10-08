/*******************************************************************************
 *
 * Point Take 2 Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include "point_take2.hpp"

point_take2::point_take2(int x, int y): x_(x), xy_(x + y) {}

void point_take2::swap_coord() {
    x_ = xy_ - x_;
}

double point_take2::ratio() const {
    return x_ / (xy_ - x_);
}

double point_take2::sum() const {
    return xy_;
}

int point_take2::getx() const {
    return x_;
}

int point_take2::gety() const {
    return xy_ - x_;
}
