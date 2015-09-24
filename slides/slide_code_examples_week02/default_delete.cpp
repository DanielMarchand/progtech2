/*******************************************************************************
 *
 * Lecture Week 02 Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <iostream>

struct base {
    
    virtual void fct1() const; // not pure (=0)
    
    virtual void fct2() const;
    
    virtual void fct3() const final; // no one writes a better version!
};

struct derived final: public base {
    
    // forgot const, no override, but no compile error
    void fct1(); 
    
    // compiler will fail if base::fct2 with this signature is not found
    void fct2() override;
    
    // works
    void fct2() const override;
    
    // fails since base::fct3 final
    void fct3() const override;
    
};

// failes since derived is final
struct no_chance: public derived {
};

// the old way of disableling special functions
class no_copy_class {
public:
    
private:
    // define copy constructor private -> copy not possible
    no_copy_class(no_copy_class const & rhs) {
    }
};

// the c++11 way of deleting special functions
class no_copy_class2 {
public:
    // you can enable the default behavior of special function
    no_copy_class2() = default;
    
    no_copy_class2(int a); // this disables the compiler-generated default-ctor
    
    // it is public information that this class is non-copyable
    no_copy_class2(no_copy_class2 const & rhs) = delete;
    
    // you can mark any function as deleted
    void some_fct() = delete;
    
private:
};



int main(int argc, char* argv[]) {
    
    return 0;
}
