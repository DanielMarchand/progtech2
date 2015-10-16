/*******************************************************************************
 *
 * Debugger Example: vector boundaries bug
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 * The program should print the mean of (1/1000, ... , 1/1010), but in most
 * cases prints inf.
 * Set a breakpoint at the std::cout line (this is where "we see" the error).
 * Step into mean() and print v. If it has an inf entry, clearly mean() is
 * already getting faulty input. It may come from invert(), so set a breakpoint
 * at that function ('b invert') and rerun the program.
 *
 * Run a few iterations ('n') of the loop and print v. Notice how in main()
 * ('bt' and change to frame 1) the vector d looks just like the vector v,
 * because the latter is a reference to d.
 * Change back to frame 0. We want to use 'c' instead of 2x 'n', so set a
 * watchpoint on the variable i (then look at 'info break' / 'watchpoint list').
 * We are interested in v[i] and 1./v[i] at every change of i.
 * In gdb:
 *   commands WATCHPOINT_NUM
 *   ...
 *   end
 * In lldb:
 *   watchpoint command add WATCHPOINT_NUM
 *   ...
 *   DONE
 * IN both, "..." is for example:
 *   print i
 *   print v._M_impl._M_start[i]
 *   print 1./v._M_impl._M_start[i]
 * 
 * Iterate ('c') until you see something suspicious.
 *
 ******************************************************************************/


#include <vector>
#include <algorithm>
#include <iostream>

std::vector<double> invert(std::vector<int> & v) {
    std::vector<double> res;
    for(decltype(v.size()) i = 0; i <= v.size(); ++i)
        res.push_back(1./v[i]);
    return res;
}

template <typename T>
double mean(std::vector<T> & v) {
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

int main() {

    std::vector<int> v;
    for(int i = 1000; i <= 1010; ++i)
        v.push_back(i);

    std::vector<double> d = invert(v);
    std::cout << mean(d) << std::endl;


    return 0;
}
