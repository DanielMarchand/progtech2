cmake_minimum_required (VERSION 2.8)
project(catch_testing)

# ================ compiler
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wpedantic")

# ================ options
OPTION(BUILD_TEST "build all the tests" ON)

set(SRC ${PROJECT_SOURCE_DIR}/src)
set(EXTERN ${PROJECT_SOURCE_DIR}/../../exercise/extern/include)
set(LIB prime_lib)

# ================ include dirs
include_directories(${SRC})
include_directories(${EXTERN})

# ================ sub dirs
add_subdirectory(src)

# ================ exes

