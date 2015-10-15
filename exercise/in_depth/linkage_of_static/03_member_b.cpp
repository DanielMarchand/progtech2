// Static member variables and methods

// Class declaration+definition, ordinarily split into .hpp/.cpp
class Foo {  
    public:
    static int x;    // external linkage, can be defined in any comiplation unit
    static int y;
    static int z;

    static int foo();
    int bar();
    int baz() { return x; }   // definition in declaration not seen in 03_member_a.cpp
};
int Foo::x = 2;
int Foo::foo() { return x; }  // definition seen in 03_member_a.cpp upon linkage
int Foo::bar() { return x; }

namespace Bar {
    int x = 2;                // external linkage
}
