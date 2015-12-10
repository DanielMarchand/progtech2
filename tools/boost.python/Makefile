# Makefile for Boost Python example

# We choose these variable names because they are used implicitly by the make
# system when there is no execution line below the 'target: dependencies' line.
CXX = g++
CPPFLAGS = -std=c++14 -O3 -fPIC -I/usr/include/python2.7
LDFLAGS = -lpython2.7
LDBOOST = -lboost_python
# Example flags if you have Boost Python built against Python 3.4:
#CPPFLAGS = -std=c++14 -O3 -fPIC -I/usr/include/python3.4
#LDFLAGS = -lpython3.4
#LDBOOST = -lboost_python3

# Measure the compilation time
TIME = `which time` -f "wall time: %e"

# Make sure these targets are not seen as files
.PHONY: all clean

# Default target
all: lib/fib.so lib/fibboost.so embedded lib/cppclass.so

# Binary shared object targets

lib/fib.so: tmp/01_capi.o
	$(TIME) $(CXX) $(CPPFLAGS) -shared $^ $(LDFLAGS) -o $@

lib/fibboost.so: tmp/02_boostpy.o
	$(TIME) $(CXX) $(CPPFLAGS) -shared $^ $(LDFLAGS) $(LDBOOST) -o $@

embedded: tmp/03_embed.o
	$(TIME) $(CXX) $(CPPFLAGS) $^ $(LDFLAGS) $(LDBOOST) -o $@

lib/cppclass.so: tmp/04_classes.o
	$(TIME) $(CXX) $(CPPFLAGS) -shared $^ $(LDFLAGS) $(LDBOOST) -o $@

# Generic target for object binaries
tmp/%.o: src/%.cpp
	@mkdir -p tmp
	$(TIME) $(CXX) $(CPPFLAGS) $< -c -o $@

# Cleanup: set to initial state
clean:
	rm -rf tmp
	rm -rf lib/*
	touch lib/__init__.py
	rm -f embedded
