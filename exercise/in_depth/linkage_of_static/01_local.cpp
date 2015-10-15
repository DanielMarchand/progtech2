// Local static variables

#include <iostream>

int foo() {
    static int x = 0;  // initial value
    ++x;
    return x;
}

int main() {
    for(int i = 0; i < 5; ++i)
        std::cout << foo() << " ";
    return 0;
}
