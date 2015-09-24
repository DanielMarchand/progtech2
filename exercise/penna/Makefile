# Makefile for the regex compilation time example

# We choose these variable names because they are used implicitly by the make
# system when there is no execution line below the 'target: dependencies' line.
CXX = g++
CPPFLAGS = -std=c++11 -O3 -Wall -Wextra -Wpedantic -Werror

# Make sure these targets are not seen as files
.PHONY: all clean

# Default target, depends on the two binary targets
all: main

# Binary targets
main: main.o sheep.o bear.o
	$(CXX) $(CPPFLAGS) $^ -o $@

# Generic target for object binaries
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $< -c

# Cleanup
clean:
	rm main
	rm *.o
