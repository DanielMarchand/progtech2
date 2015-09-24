/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

// I ommit "const &" and further technical details for readibility
#include <cmath>

// problem, not working...
#include "simpson.hpp"
#include <iostream>

// a function with two variables
double exp_ax(double a, double x) {
    return std::exp(a*x);
}

int main1() {
    // where do we set a?
    //~ std::cout << simpson(exp_ax, 0, 1, 100) << std::endl;
    // does not compile since exp_ax has signature 
    // double(double, double) and not double(double)
    return 0;
}


// global variable "solution"
#include "simpson.hpp"
#include <iostream>

// an ugly global variable
double a;

// the function to be integrated
double exp_a_glob(double x) {
    return std::exp(a*x);
}

int main2() {
    a = 3.4;
    std::cout << simpson(exp_a_glob, 0, 1, 100) << std::endl;
    return 0;
}


// a function object for exp(a*x)
#include "simpson.hpp"
#include <iostream>

class exp_fct_obj {
    public:
    // set the parameter a in the constructor
    exp_fct_obj(double a) : a_(a) {}

    // the function call operator calculates the function
    double operator()(double x) { 
        return std::exp(a_*x);
    }

    private:
    double a_; // the fixed parameter a
};

int main3() {
    double a = 3.4;
    std::cout << simpson(exp_fct_obj(a), 0, 1, 100) << std::endl;
    return 0;
}

// bind solution
#include "simpson.hpp"
#include <iostream>
#include <functional> // for std::bind

int main4() {
    using namespace std::placeholders; // for _1
  
    double a = 3.4;
    // bind one argument: _1, _2, .... are used for 
    // unbound arguments of the resulting function
    auto exp_bind_a = std::bind(exp_ax, a, _1);
    
    std::cout << simpson(exp_bind_a, 0, 1, 100) << std::endl;
    return 0;
}

// lambda functions
#include "simpson.hpp"
#include <iostream>

int main5() {
    double a = 3.4;

    // create a lambda function
    // [=] indicates that all variable 
    // used inside the lambda are passed by value
    auto exp_a_lambda = [=](double x){ return exp_ax(a, x); };

    std::cout << simpson(exp_a_lambda, 0, 1, 100) << std::endl;
    return 0;
}

// inline lambda
#include "simpson.hpp"
#include <iostream>

int main6() {
    double a = 3.4;
    std::cout << simpson([=](double x){ return exp_ax(a, x); }, 0, 1, 100) << std::endl;
    return 0;
}

// std::function
#include <vector>

int main7() {
    using namespace std::placeholders;
    double a = 3.4;
    
    std::vector<std::function<double(double)>> fct;
    
    fct.push_back(exp_a_glob);               // normal function
    fct.push_back(exp_fct_obj(a));           // function object
    fct.push_back(std::bind(exp_ax, a, _1)); // function via bind
    fct.push_back([=](double x){ return exp_ax(a, x); }); // lambda function
    
    for(auto f: fct)
        std::cout << simpson(f, 0, 1, 100) << std::endl;
        
    
    return 0;
}

int main() {
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();
}
