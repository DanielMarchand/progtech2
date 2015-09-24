# Makefile for Penna

# We choose these variable names because they are used implicitly by the make
# system when there is no execution line below the 'target: dependencies' line.
CXX = g++
CPPFLAGS = -std=c++11 -O3 -Wall -Wextra -Wpedantic -Werror

# The base source and target directories
SOURCE = ./
BUILD = ./

# Our targets and headers that correspond to an object
OBJECTS_1 = $(BUILD)/main.o $(BUILD)/sheep.o
BINARY_1 = main
HEADER_WITH_OBJ = $(SOURCE)/sheep.hpp
# adding new name.o <-> name.hpp couplings with: HEADER_WITH_OBJ += sheep2.hpp

# Default target
all: $(BINARY_1)

# Make sure these targets are not seen as files
.PHONY: all clean

# Binary targets
$(BUILD)/$(BINARY_1): $(OBJECTS_1)
	@echo ">" building $@
	$(CXX) $(CPPFLAGS) $^ -o $@

# Generic target for object binaries. Appending %.hpp doesn't match this rule on main.cpp
$(BUILD)/%.o: $(SOURCE)/%.cpp
	@echo ">" generic rule for $@
	$(CXX) $(CPPFLAGS) $< -c -o $@

# Workaround: adds trigger on headers modification (obj.o: obj.hpp)
$(foreach FILENAME, $(HEADER_WITH_OBJ), $(eval \
$(subst $(SOURCE), $(BUILD), $(addsuffix .o,$(basename $(FILENAME)) )): $(FILENAME)\
))

# Cleanup
clean:
	rm -f main
	rm -f *.o
