/*******************************************************************************
 *
 * Debugger Example: examine variables
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 * Set a breakpoint at the push_back line and run the program.
 * Check the vector ('print v') after iterating with 'c' ('continue') or 'n'
 * ('next' line).
 * Also check the position of the vector implementation, which are the values of
 * the pointers
 *   v._M_impl._M_start, v._M_impl._M_finish and v._M_impl._M_end_of_storage,
 * for different types of std::vector (int, char, double).
 *
 * Delete the old breakpoints ('del break' in gdb / 'break del' in lldb) and
 * add a conditional one ('break FILENAME:NUMBER if i > 5' /
 *  'break set --file FILENAME --line NUMBER --condition "i > 5" ').
 * Rerun the program ('kill' 'run'), change a variable
 * ('set var i = 8' / 'expr i = 8') and check how the vector behaves when
 * iterating ('c').
 *
 * Delete the breakpoints (you can check them with 'info break' / 'break list'
 * and delete only specific numbers) and break at the bar() function
 * ('break bar' / 'b bar'), then rerun the program.
 * Check x ('print x') and again after the assignment ('n').
 * Check the frame stack ('backtrace' / 'bt'), change to a lower frame
 * ('frame 1' / 'frame sel 1'), which will show you the current foo() local, and
 * check x there. Shifting back to frame 0 will show you bar()'s local again.
 *
 * The 'disassemble' command will show the current assembly representation of
 * the function. Keep in mind that this is the most similar to your source code
 * when compiling with -O0. You can execute the individual instructions with
 * 'stepi' (check the position of the arrow in the 'disassemble' command).
 *
 * Delete all breakpoints and set one at the main function ('b main'). You can
 * set/edit arbitrary variables and call any functions ('call foo()'). Progress
 * with 'n' until the push_back. You can step into the function at the current
 * breakpoint with 'step' (in lldb, you might have to issue multiple 'stepi'
 * instead, since this is a linked STL function), look around there
 * ('bt' or 'info loc' / 'frame var') and step into further functions or exit
 * with 'finish'.
 * Don't be scared by the amount of template expressions in the STL, at the end
 * of this course, you can understand it all!
 *
 ******************************************************************************/

#include <iostream>
#include <vector>

void bar() {
    int x = 2;
}
void foo() {
    int x = 1;
    std::cout << "foo " << x << std::endl;
    bar();
}

int main() {

    std::vector<double> v;
    for(int i = 0; i < 15; ++i)
        v.push_back(i);

    foo();

    return 0;

}
