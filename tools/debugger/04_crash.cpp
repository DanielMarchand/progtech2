/*******************************************************************************
 *
 * Debugger Example: crash diagnostics
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 * When run normally, these programs simply segfault.
 * When run in a debugger, you get the source code location of the crash site
 * and full access to the environment ('info locals' / 'frame var',
 * 'disassemble')!
 *
 ******************************************************************************/

#include <vector>
#include <iostream>

template <typename T>
void crash(T & v) {
    //v[-1] = 3;
    std::cout << v[111111] << std::endl;
}

int main() {

    std::vector<int> v;

    crash(v);

    return 0;

}
