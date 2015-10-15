// Static member variables and methods

#include <iostream>

// Class declaration, ordinarily goes into .hpp
class Foo {
    public:
    static int x;        // external linkage, declaration here, can be defined in any compilation unit, same for all instances
    static int y;        // same as above
    static int z;        // same as above
    //static int u = 5;  // error: can't define non-const (=changeable) static (could modify without object! where to store this?)

    static int foo();    // can only access static members (because we don't have a this-pointer)
    int bar();
    static int baz();
};

//int Foo::x = 1;        // conflicts with definition in 03_member_b.cpp
//static int Foo::x = 1; // static in just definition (after declaration) is invalid syntax

int Foo::y = 3;

// Comparison of class with namespace
namespace Bar {
    //int x = 1;         // conflicts with definition in 03_member_b.cpp
    static int x = 1;    // if this were possible, would correspond to something like 'static static int x' in a class
    int y = 3;           // external linkage, corresponds to class static member
}

int main() {

    std::cout << "Foo::x=" << Foo::x << " ";
    std::cout << "Foo::y=" << Foo::y << " ";
    //std::cout << "Foo::z==" << Foo::z << " ";          // fails, declared but not defined anywhere

    std::cout << "Foo::foo()==" << Foo::foo() << " ";
    //std::cout << "Foo::bar()==" << Foo::bar() << " ";  // fails, not static, can't call without object of type Foo
    //std::cout << "Foo::baz()==" << Foo::baz() << " ";  // fails, not "sufficiently" defined in 03_member_b.cpp

    // access namespace variables like class static members, but the similarity ends here
    std::cout << "Bar::x==" << Bar::x << " ";            // internal linkage
    std::cout << "Bar::y==" << Bar::y << " ";            // external linkage

    return 0;

}
