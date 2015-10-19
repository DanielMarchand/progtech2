# Debugger

### Why do we need an error finding tool (debugger)?

* ___find errors quickly___ without `cout << "A"; /*...*/ cout << "B";` bisection
* diagnose segfaults/crashes with ___full state information___
* efficiently ___fix mistakes___ in list manipulation, range access, dispatching, ...
* resolve inexplicable errors

### What do we expect from our debugger?

* ___stop___ the program at any point in the execution flow
* look at the ___value of any symbol___ in the program memory
* show ___instantiated code___: object dumps, template instances, current loop state 
* ___connect___ source code (lines and blocks) with execution flow
* show a ___backtrace___ of the current stack frames, print each caller ___function state___
* ___monitor___ variables and execute statements when certain ___conditions___ are met
* alter ___program flow___ of a live binary
* ~~easy~~ not very hard to use
* ~~fast~~ not extremely slow

## gdb & lldb

In this course we will use [gdb](https://www.gnu.org/software/gdb/) (on GNU/Linux) and [lldb](http://lldb.llvm.org/) (on GNU/Linux and OSX).<br />
Follow the [debugger lecture example](tools/debugger) to acquire the skills needed.<br />
A full [gdb tutorial](https://sourceware.org/gdb/download/onlinedocs/gdb/index.html) and [lldb tutorial](http://lldb.llvm.org/tutorial.html) can be found online.<br />

## Other debuggers

**[Valgrind](http://valgrind.org/)**: virtual machine with tools for detailed analysis of memory/cache/function/heap/... accesses.<br />
**[WinDbg](www.microsoft.com/whdc/devtools/debugging/default.mspx)**: common debugger on Microsoft Windows<br />

