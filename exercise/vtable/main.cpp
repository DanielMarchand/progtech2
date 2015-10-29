#include "veggies_crtp.hpp"

int main() {

    int time = 14_days;  // OneDimVegetables grow by the hour, but we use days

    Carrot ca;
    Cucumber cu;
    auto cap = new Carrot();
    OneDimVegetable<Carrot> * vp = new Carrot();

    // Growth rates per month curtesy from Wikipedia. They vary.
    while(time--) {
        ca.grow(4.9_growth_per_month);
        cu.grow(100_growth_per_month);
        cap->grow(5_rowth_per_month);
        vp->grow(5.1_growth_per_month);
    }

    // print all the grown vegetables
    ca.print();
    cu.print();
    cap->print();
    vp->print();

    return 0;

}
