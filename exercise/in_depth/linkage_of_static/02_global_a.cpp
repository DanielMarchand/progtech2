// Global static variables/functions

#include <iostream>

//int x = 1;         // external linkage, conflicts with x from 02_global_b.cpp

static int x = 3;    // internal linkage, declares x for this compilation unit ONLY, overrides "imported" x

extern int y;        // external linkage, we expect y to be "imported" (== defined == initialised) through linking
                     //                   this tells the compiler to not allocate any space for the variable

static int z = 5;    // definition (without assignment, this is implicitly defined as 0)
extern int z;        // declaration, compiler sees that the symbol already exists, we can declare things multiple times, z stays defined static

extern int u;        // external linkage, we might later link some object defining u even though it's not in 02_global_b.cpp
//static int u;      // fails (C++ Standard, Section 3.5.6), definition is "stricter" than declaration and u is already declared in a way incompatible with static

extern int v;        // here's a small brain teaser :)
int w = v+1;

static int foo() {   // internal linkage: this function can't be used in any other file
    return 7;
}

int bar();           // external linkage: declared here, will be linked against unique (!) definiton from somewhere

extern int baz();    // external linkage: for functions, this is the default and can be omitted


int main() {
    std::cout << "x==" << x << " ";
    std::cout << "y==" << y << " ";
    std::cout << "z==" << z << " ";
    //std::cout << "u==" << u << " ";  // linker error: no u in any linked objects (02_global_b.o)
    std::cout << "v==" << v << " ";
    std::cout << "w==" << w << " ";
    std::cout << "foo()==" << foo() << " ";
    std::cout << "bar()==" << bar() << " ";
    //std::cout << "baz()==" << baz() << " ";  // linker error: no baz in any linked objects (02_global_b.o)
    return 0;
}
