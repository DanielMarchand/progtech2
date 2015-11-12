# Makefile for thunder-structs

CXX = g++
CPPFLAGS = -Wall -Wextra -Wpedantic -std=c++14 -O3

.PHONY: all what clean run

all: arena

arena: arena.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

clean:
	rm -f arena

what:
	@echo "AVAILABLE TARGETS:"
	@cat "Makefile" | grep -Pv '^(#|\s)' \
		| grep --only-matching '^.*:' \
		| grep -v '^.*=' \
		| sed 's/://' | grep -v ',' \
		| grep -v '^.PHONY' | grep -v '^.SUFFIXES'
