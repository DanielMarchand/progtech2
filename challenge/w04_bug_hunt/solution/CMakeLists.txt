cmake_minimum_required (VERSION 2.8)
project(challenge_bug_hunt)

# ================ compiler
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wpedantic")

set(SRC ${PROJECT_SOURCE_DIR}/src)
set(EXTERN ${PROJECT_SOURCE_DIR}/../../../exercise/extern/include)
set(LIB mymath_lib)

# ================ include dirs
include_directories(${SRC})
include_directories(${EXTERN})

# ================ sub dirs
add_subdirectory(src)

add_subdirectory("test")

