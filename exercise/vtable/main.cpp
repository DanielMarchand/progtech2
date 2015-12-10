/*******************************************************************************
 *
 * Simplified demonstration of a growable concept for vegetables
 * Requires -std=c++14.
 * 
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved, no warranty whatsoever.
 * 
 ******************************************************************************/

#include <vector>
#include "veggies_crtp.hpp"

struct growable_base { // polymorphic base class
    virtual ~growable_base() {}

    virtual void print() const = 0;
    virtual void grow(const double &) = 0;
};


template <typename T>
struct growable_impl : public growable_base { // concept holder
    growable_impl(T t) : t_(t) {}
    T t_;

    void print() const override { // concept implementation
        t_.print();
    }
    void grow(const double & d) override { // concept implementation
        t_.grow(d);
    }
};

struct growable {  // wrapper
    template <typename T>
    growable(T && t) : p_(new growable_impl<T>(t)) {}
    std::unique_ptr<growable_base> p_;

    void print() {
        p_->print();
    }
    void grow(const double & d) {
        p_->grow(d);
    }
};

// A function taking any object that fulfills the growable concept.
// The type for the parameter g doesn't have to derive from a base of the input.
void supergrow(growable g) {
    g.grow(333.3);
}

int main() {

    int time = 14_days;  // OneDimVegetables grow by the hour, but we use days

    Carrot ca;
    Cucumber cu;
    auto cap = new Carrot();
    OneDimVegetable<Carrot> * vp = new Carrot();

    std::vector<growable> vec;
    vec.push_back(ca);
    vec.push_back(cu);
    vec.push_back(*cap);
    vec.push_back(*vp);

    supergrow(*cap);

    // Growth rates per month curtesy from Wikipedia. They vary.
    while(time--) {
        ca.grow(4.9_growth_per_month);
        cu.grow(100_growth_per_month);
        cap->grow(5_growth_per_month);
        vp->grow(5.1_growth_per_month);
    }
    // print all the grown vegetables
    for(auto elem: vec)
        elem.print();

    return 0;

}
