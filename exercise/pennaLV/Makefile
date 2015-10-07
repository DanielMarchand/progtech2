# Makefile for PennaLV

# We choose these variable names because they are used implicitly by the make
# system when there is no execution line below the 'target: dependencies' line.
CXX = g++
CPPFLAGS = -std=c++11 -O3 -Wall -Wextra -Wpedantic -Werror
VPATH = src

# Source and target directories
BUILD = ./build
MKBUILDDIRS = ./build ./build/zoo
INCLUDE_DIR = ../extern/include

# Our targets and headers that correspond to an object
OBJECTS_1 = $(BUILD)/main.o $(BUILD)/zoo/animal.o $(BUILD)/zoo/sheep.o $(BUILD)/zoo/bear.o
BINARY_1 = main
HEADER_WITH_OBJ  = zoo/animal.hpp
HEADER_WITH_OBJ += zoo/sheep.hpp
HEADER_WITH_OBJ += zoo/bear.hpp

# Make sure these targets are not seen as files
.PHONY: all clean prepare_build

# Default target
all: prepare_build $(BUILD)/$(BINARY_1)

# Prepare build directory structure
prepare_build:
	mkdir -p $(MKBUILDDIRS)

# Binary targets
$(BUILD)/$(BINARY_1): $(OBJECTS_1)
	@echo ">" building $@
	$(CXX) $(CPPFLAGS) $^ -o $@

# Generic target for object binaries. Appending %.hpp doesn't match this rule on main.cpp
$(BUILD)/%.o: $(VPATH)/%.cpp
	@echo ">" generic rule for $@
	$(CXX) $(CPPFLAGS) $< -c -o $@ -I $(INCLUDE_DIR)

# Workaround: adds trigger on headers modification (name.o: name.hpp)
$(foreach FILENAME, $(HEADER_WITH_OBJ), $(eval \
$(subst $(VPATH), $(BUILD), $(addsuffix .o,$(basename $(FILENAME)) )): $(FILENAME)\
))

# Cleanup
clean:
	rm -rf $(BUILD)/*
