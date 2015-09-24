/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <list>
#include <vector>
#include <iostream>

// normally used for namespaces
using namespace std;

// suppose a project uses a int and double vector

typedef std::vector<double> d_container_type1;
typedef std::vector<int> i_container_type1;

// lets say we want to change the container to list
// we have to change all typedefs...
typedef std::list<double> d_container_type2;
typedef std::list<int> i_container_type2;


// with c++11 we can change typedef with using
// nicer syntax, especially for function pointer typedefs
typedef void (*FP)(double, double);
using FP2 = void (*)(double, double);

using d_container_type3 = std::vector<double>;
using i_container_type3 = std::vector<int>;


// but the real power of using lies in 
// the possibility to template it

template<typename T>
using container_type1 = std::vector<T>;

using d_container_type4 = container_type1<double>;
using i_container_type4 = container_type1<int>;


// if I want to change vector to list now
// only one using needs to be changed
template<typename T>
using container_type2 = std::list<T>;

// using should become your default way of setting type-alias


// sidenote: remember "typename" if you have dependent types?
template<typename T>
struct echo_type1 {
    typedef T type;
};

template<typename T>
struct dependent_demo1 {
    //~ typedef echo_type1<T>::type type; // will not compile
    typedef typename echo_type1<T>::type type; // typename is needed
};


// no need for this with using, since the compiler knows it's a type
template<typename T>
using echo_type2 = typename echo_type1<T>::type; // hide typename ... ::type here

template<typename T>
struct dependent_demo2 {
    using type = echo_type2<T>; // much much nicer to use
};

#include <type_traits>

// so nice in fact, c++14 introduces new type traits
template<typename T>
struct type_trait_demo {
    using old_way = typename std::remove_const<T>::type;
    //~ using new_way = std::remove_const_t<T>;
};


int main(int argc, char* argv[]) {
        
    d_container_type1 a1;
    i_container_type1 b1;
    
    d_container_type2 a2;
    i_container_type2 b2;
    
    d_container_type3 a3;
    i_container_type3 b3;
    
    d_container_type4 a4;
    i_container_type4 b4;
    
    dependent_demo1<int>::type d1;
    dependent_demo2<int>::type d2;
    
    return 0;
}
