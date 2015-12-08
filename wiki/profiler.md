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

