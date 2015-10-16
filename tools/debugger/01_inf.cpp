/*******************************************************************************
 *
 * Debugger Example: infinite loop
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 * If you run ('run' command in a debugger) the code with d = 11, it will hang.
 * Interrupt the execution (Ctrl-C or Cmd-C), which allows you to examine the
 * current state of the program:
 * - current location with the 'backtrace' (for gdb) / 'bt' (for lldb) command
 * - local variables ('info locals' / 'frame variable')
 * - watch how a local variable ('watch e' / 'watch set var e') changes after
 *   iterations ('c' or 'continue' to the next break/watch event).
 *
 * Observing the large value for e allows us to see that it has passed beyond
 * the e != d check, which is incorrect code.
 *
 * Hint: in both debuggers, use the tabulator key (a lot!) to show available
 *       commands/subcommands and autocomplete them.
 *
 ******************************************************************************/

#include <iostream>

double sum_deci(double d) {
    double res = 0;
    for(double e = d/10; e != d; e += d/10)
        res += e;
    return res;
}

int main() {

    //~ double d = 10;
    //~ double d = 15;
    double d = 11;
    std::cout << sum_deci(d) << std::endl;

    return 0;

}
