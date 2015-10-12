cmake_minimum_required (VERSION 2.8)
project(penna_lv_simulation)

# ================ compiler
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wpedantic")

set(SRC ${PROJECT_SOURCE_DIR}/src)
set(EXTERN ${PROJECT_SOURCE_DIR}/../extern/include)
set(LIB zoo_lib)

# ================ include dirs
include_directories(${SRC})
include_directories(${EXTERN})

# ================ sub dirs
add_subdirectory(src)

# ================ exes

