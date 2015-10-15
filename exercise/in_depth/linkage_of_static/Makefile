# Makefile for static linkage example

CXX = g++
CPPFLAGS = -Wall -Wextra -Wpedantic

PREPARE_BUILD = @mkdir -p build
BUILD = $(CXX) $(CPPFLAGS) $^ -o build/$@
RUN = @echo Running build/$@:"\n"`build/$@`

.PHONY: all what clean

all: what

01_local: build/01_local.o
	$(BUILD)
	$(RUN)

02_global: build/02_global_a.o build/02_global_b.o
	$(BUILD)
	$(RUN)

03_member: build/03_member_a.o build/03_member_b.o
	$(BUILD)
	$(RUN)

build/%.o: %.cpp
	$(PREPARE_BUILD)
	$(CXX) $(CPPFLAGS) $^ -c -o $@

clean:
	rm -f build/*

what:
	@echo "AVAILABLE TARGETS:"
	@cat "Makefile" | grep -Pv '^(#|\s)' \
		| grep --only-matching '^.*:' \
		| grep -v '^.*=' \
		| sed 's/://' | grep -v ',' \
		| grep -v '^.PHONY' | grep -v '^.SUFFIXES'
