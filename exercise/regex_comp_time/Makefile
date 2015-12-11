# Makefile for the regex compilation time example

# We choose these variable names because they are used implicitly by the make
# system when there is no execution line below the 'target: dependencies' line.
CXX = g++
CPPFLAGS = -std=c++11 -O2

# Measure the compilation time
TIME = `which time` -f "wall time: %e"

# Make sure these targets are not seen as files
.PHONY: all clean

# Default target, depends on the two binary targets
all: fast slow

# Binary targets
fast: fast.o reg.o reg.hpp
	$(TIME) $(CXX) $(CPPFLAGS) -o $@ $^
slow: slow.o
	$(TIME) $(CXX) $(CPPFLAGS) -o $@ $^

# Generic target for object binaries, with Automatic Variables
%.o: %.cpp ; $(TIME) $(CXX) $(CPPFLAGS) -c -o $@ $<

# Cleanup
clean:
	rm fast slow
	rm *.o
