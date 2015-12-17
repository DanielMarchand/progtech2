# Makefile for random.hpp boost::python extension

CXX = g++
CPPFLAGS = -std=c++14 -O3 -Wall -Wextra -Wpedantic -Werror
CPPFLAGS += -fPIC
CPPFLAGS += -I/usr/include/python2.7
LDFLAGS = -shared -lpython2.7 -lboost_python

.PHONY: all clean

all: boostpy_random.so

# Generic target for shared object binaries, with Automatic Variables
%.so: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm *.so
