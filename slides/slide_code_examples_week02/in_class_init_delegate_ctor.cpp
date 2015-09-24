/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>

// c++98 problems
class myclass {
public:
    myclass(): c_num_(10), num_(42) {}
    
    myclass(int nr): c_num_(10), num_(nr) {}
    
    myclass(int nr1, int nr2): c_num_(10), num_(nr1 + nr2) {}
    
    // we write three times c_num_(10)...
    
    void print() {
        std::cout << c_num_ << " " << num_ << std::endl;
    }
private:
    int c_num_;
    int num_;
};

// c++11 delegating ctors
class myclass2 {
public:
    // delegates to myclass(int)
    myclass2(): myclass2(42) {}
    
    // only one ctor needs to init members
    myclass2(int nr): c_num_(10), num_(nr) {}
    
    // delegates to myclass(int)
    myclass2(int nr1, int nr2): myclass2(nr1 + nr2) {}
    
    void print() {
        std::cout << c_num_ << " " << num_ << std::endl;
    }
private:
    int c_num_;
    int num_;
};

// c++11 even better: in-class member initializer
class myclass3 {
public:
    // delegates to myclass(int)
    myclass3(): myclass3(42) {}
    
    // only one ctor needs to init members
    myclass3(int nr): c_num_(10), num_(nr) {}
    
    // delegates to myclass(int)
    myclass3(int nr1, int nr2): myclass3(nr1 + nr2) {}
    
    void print() {
        std::cout << c_num_ << " " << num_ << std::endl;
    }
private:
    int c_num_ = 10; // can overwritten by ctor (but doesn't have to)
    int num_; 
};


int main(int argc, char* argv[]) {
    
    myclass a0;
    myclass a1(1);
    myclass a2(1, 1);
    
    a0.print();
    a1.print();
    a2.print();
    
    myclass2 b0;
    myclass2 b1(1);
    myclass2 b2(1, 1);
    
    b0.print();
    b1.print();
    b2.print();
    
    myclass3 c0;
    myclass3 c1(1);
    myclass3 c2(1, 1);
    
    c0.print();
    c1.print();
    c2.print();
    
    return 0;
}
