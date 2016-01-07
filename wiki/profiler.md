# Profiler

### Why do we need a profiler?

* ___dynamic___ performance analysis in ___real___ world deployment
* identify specific ___bottlenecks___, because:
    - premature optimisation is evil
    - we strive for readability and maintainability

### What do we expect from our profiler?

* ___truthfully___ represent behaviour of program (no bias / interference)
* provide data with high ___accuracy___
* show ___cpu cycles___, ___wall time___, ___memory access counters___
* show function ___call graph___ and ___count___
* various ___outputs___:
    - table with statistics
    - trace (instruction path)
    - live monitoring
* different ___collection___ methods:
    - event-based (interrupt)
    - statistical (sampling)
    - instrumented (injection at source level, in bytecode or RAM)
    - simulation (virtual machine)
* high level ___assessment___
* automatic compiler / toolchain feedback
* easy to use
* somewhat fast
* portability is no big concern

## Profiling tools

Here is a brief selection of profiling tools and techniques as shown in the lecture.
In order to produce debugging information, we generally add the `-g` flag to
the compiler options, which is equivalent to setting the build type to `Debug`
in cmake/ccmake.<br />
To get a realistic picture, we also want to set the same full optimisation flags
we use in the release version.

#### gprof

The [GNU profiler](https://sourceware.org/binutils/docs/gprof/) is a simple yet
useful GNU/Linux-based compiler-level instrumentation profiler which requires
`-pg` to be added to the compiler flags.<br />
After compilation, executing the binary (e.g. `src/main`) will produce a statistical call
graph profile called `gmon.out` in the current directory. We can then see the relations
between the symbol table of the binary and the execution profile by running

    gprof src/main > info.txt

and viewing `info.txt` (which contains three documented sections) in any text editor.

Further instructions, e.g. how to generate call graphs, can be found in the
[gprof documentation](https://sourceware.org/binutils/docs/gprof/).

#### perf

A versatile [Linux kernel performance counter](https://perf.wiki.kernel.org/index.php/Main_Page)
tool for either specific binaries or the entire system.

We can obtain a brief execution summary by running the statistics subcommand:

    perf stat src/main

Detailed data can be collected by recording the execution into a `perf.data` file
and reporting on it (type `?` while in the report tool for more info):

    perf record src/main
    perf report

To generate a call graph visualisation, we record the stack chain / backtrace information:

    perf record -g -- src/main

Then we run the perf script command with `c++filt` (demangle C++ function names) and
`gprof2dot` (dot grapher for, among others, perf; available via pip):

    perf script | c++filt | gprof2dot -f perf | dot -Tpng -o out.png

This creates a nice visual representation of function calls and work effort percentages in `out.png`.

Live analysis, code annotation, various benchmarks for schedulers or memory access
and many other features can be read up about in the
[perf tutorial](https://perf.wiki.kernel.org/index.php/Tutorial).

#### Valgrind

[Valgrind](http://valgrind.org/) is a cross platform (GNU/Linux, OSX, Solaris)
virtual machine used for [debugging](wiki/debugger.md) in a variety
of areas (most popularly via the `memcheck` tool).

Among profiling options, we can obtain a short summary of the cache performance:

    valgrind --tool=cachegrind src/main

which also generates a detailed cachegrind.out.* report that can be assessed with:

    cg_annotate cachegrind.out.NUM > info.txt

We can as well investigate the amount dynamic memory used by our program with Valgrind's heap profiler:

    valgrind --tool=massif src/main
    ms_print massif.out.NUM > info.txt

Another interesting use of Valgrind is live viewing the current stack frame backtrace.<br />
In one terminal, we can observe any program under callgrind's control (abort with Ctrl+c):

    `which watch` -pn 0.1 callgrind_control -b -e

While in another terminal, we execute the program:

    valgrind --tool=callgrind src/main

Detailed explanation of the mentioned commands and a wealth of other applications
(e.g. generating call graphs) can be found in the
[Valgrind manual](http://valgrind.org/docs/manual/manual.html).

#### gcov & lcov

gcov is a cross platform (Unix-like) code coverage and statement-level profiling
tool from the GCC suite, used to generate line-by-line profiles, annotated source
listings and perform basic-block counting.<br />
It requires the g++ compiler flags `-fprofile-arcs` (injects branch/call counters
and produces `.gcda` files) and `-ftest-coverage` (produces `.gcno` files
documenting code coverage).<br />
The flag `--coverage` is a shortcut for these two settings.

After compilation, we can run the program (e.g. `src/main`), which will generate
`.gcda` and `.gcno` data next to each compiled object file in the build directory.
We can find those with:

    find -iname "*.gc*"

These allow us to generate annotated versions of all source files that went into
creating a specific object file:

    gcov ./src/CMakeFiles/main.dir/main.cpp.gcda

Now we can look at `main.cpp.gcov` or `sheep.hpp.gcov` in the current directory
to see how many times each line in those files was executed.

Further information can be found in the [gcov documentation](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html).

[lcov](http://ltp.sourceforge.net/coverage/lcov.php) is an extension to gcov,
enabling the generation of pretty HTML output.

Having run the binary with the `--coverage` flag, we can create a trace file and
and use it to build a html documentation:

    lcov --capture --directory src/CMakeFiles/main.dir/ --output-file cov.info
    genhtml cov.info --output-dir lcov_html
    firefox lcov_html/index.html

This allows us to check in a convenient manner how much of the source code was
executed how often (or at all) in a particular run.

#### Other profilers

There are many other profiling tools. A very popular choice is
[Intel VTune](https://software.intel.com/en-us/intel-vtune), which can be obtained
via [academic licensing](https://software.intel.com/en-us/qualify-for-free-software).<br />
On Linux, [OProfile](http://oprofile.sourceforge.net/news/) is widely used.

For simple yet highly accurate and verbose cycle usage measurement, we recommend
the [Microbenchmark tool](exercise/extern/include/util/profiler.hpp) which was
[presented](tools/exercise_extern_tools/measure_perf_demo.cpp) in the lecture.
