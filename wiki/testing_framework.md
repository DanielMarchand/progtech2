# Testing

### Why do we need tests?
* ensure ___correctness___ of our code
* help for ___debugging___
* tests are often useful code ___examples___ of how to use a library

### What do we expect from our testing framework?

* platform independent
* easy setup
* informative (with color)
* notify when test fails / is done
* accept source & build tool
* integration (only allow to commit if tests work)
* granularity (small low level test and system-wide tests)
* easy to use (make test)
* fast
* statistics (test-coverage, how many parts of the code are tested)
* check-correctness of:
    - output-data (business-logic)
    - interface
    - performance
    - invarinats
    - different levels
    - call count
    - correct errors

## Catch
In this course we will use [Catch](https://github.com/philsquared/Catch). It is 
very lightweight and needs only one [header file](https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp).<br />
It's functionality is enough for a small project. For a tutorial, have a look at the <br />
documentation on Github or consider our [example code](https://gitlab.phys.ethz.ch/progtech2_hs15/lecture/tree/master/tools/catch): <br />
It shows you how to write tests and how to link the main function with CMake, <br />
such that all tests get automatically registered.

## Other testing frameworks
There are many other testing frameworks for all different languages. 
See [Wikipedia](https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks) for a large list. <br />
[Google's testing framework](https://github.com/google/googletest) offers 
many more features and an extensive documentation. <br /> 
It comes at the cost that you 
need to compile it. Consider it when doing larger projects. <br />
It also comes with a  Mocking framework.
