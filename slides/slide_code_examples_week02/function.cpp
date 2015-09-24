/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <functional>
#include "pretty_type_print.hpp"

void add_5(int & in) {
    in += 5;
}

struct add_X {
    add_X(int val): val(val) {
    }
    void operator()(int & in) {
        in += val;
    }
    int val;
};

class myclass {
    public:
    void sub(int & in) {
        in -= val;
    }
    
    int val = 5;
};

int main() {
    int val = 0;
    std::cout << val << std::endl;
    
    // use normal function
    add_5(val);
    
    // use function object
    add_X(4)(val);
    
    // use c++11 lambda
    int Y = 6;
    auto add_Y = [&](int & in){in += Y;};
    add_Y(val); // adds 6
    
    // sidenote: each lambda has it's own unique type
    PRINT_TYPE_OF(add_Y) //  main::{lambda(int&)#1}
    
    auto add_Y2 = [&](int & in){in += Y;};
    PRINT_TYPE_OF(add_Y2) // main::{lambda(int&)#2}
    
    // Y was captured per reference [&]
    Y = 1;
    add_Y(val); // now only adds 1
    
    std::cout << val << std::endl; // 5 + 4 + 6 + 1 = 15
    
    // can hold anything that is callable with the signature
    std::vector<std::function<void(int&)>> fct_vec;
    
    fct_vec.push_back(add_5);    // normal function
    fct_vec.push_back(add_X(4)); // function object
    fct_vec.push_back(add_Y);    // lambda function
    
    int val2 = 0;
    for(auto fct: fct_vec)
        fct(val2);
    
    std::cout << val2 << std::endl; // 5 + 4 + 1 = 10
    
    using namespace std::placeholders;
    
    
    auto add_x_y_z = [](int x, int y, int z)->int {return x + y + z;};
    
    auto xyz = add_x_y_z(1, 2, 3);
    std::cout << xyz << std::endl; // 1 + 2 + 3 = 6
    
    auto add_x_y_8 = std::bind(add_x_y_z, _1, _2, 8);
    
    auto xy8 = add_x_y_8(1, 2);
    std::cout << xy8 << std::endl; // 1 + 2 + 8 = 11
    
    auto add_x_1_8 = std::bind(add_x_y_8, _1, 1);
    
    auto x18 = add_x_1_8(1);
    std::cout << x18 << std::endl; // 1 + 1 + 8 = 10
    
    auto add_4_1_8 = std::bind(add_x_1_8, 4);
    auto _418 = add_4_1_8();
    std::cout << _418 << std::endl; // 4 + 1 + 8 = 13
    
    // even methods are possible
    myclass mc;
    auto free_sub = std::mem_fn(&myclass::sub);
    // free_sub(mc, val2) === mc.sub(val2)
    auto free_sub_mc = std::bind(free_sub, mc, _1);
    fct_vec.push_back(free_sub_mc);
    
    return 0;
}
