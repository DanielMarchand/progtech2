# Build system

### Why do we need a build system?

* ___compile large projects___ without a lot of manual work
* build ___different versions___ (target architecture, debug build, distribution package)

### What do we expect from our build tool?

* translates C++ ___source___ files to executable ___binaries___
* automatically resolves ___dependencies___
* knows about the ___hardware___ it's running on
* automatically ___finds libraries___ we tell it to use
* chooses the ___proper compiler___ (can be specified)
* enables different ___build versions___
* enables our program to be ___installed and/or packaged___
* ___platform independent___
* facilitates unit testing
* easy to use
* ___fast___ and ___parallel___ operation
* customisable

## CMake

In this course we will use [CMake](https://cmake.org/).<br />
Follow the [build system lecture example](tools/cmake) to acquire the skills needed.<br />
A full [tutorial](https://cmake.org/cmake-tutorial/) can be found online.<br />

## Other build systems

**[make](https://www.gnu.org/software/make/)**: executes manually written [`Makefile` recipes](http://mrbook.org/blog/tutorials/make/)<br />
**GNU [autotools](http://www.gnu.org/software/autoconf/autoconf.html)**: generates Makefiles and `configure` scripts out of `configure.ac` files<br />
**[Scons](http://www.scons.org/)**: highly flexible Python-based build system<br />
**[Jam](http://www.perforce.com/resources/documentation/jam)**: lightweight and featureful replacement for Makefiles<br />

There are [many many more](https://en.wikipedia.org/wiki/List_of_build_automation_software).
