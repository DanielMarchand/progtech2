cmake_minimum_required (VERSION 2.8)
project(cmake_tutorial)

# ================ compiler
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

# ================ include dirs
include_directories(${PROJECT_SOURCE_DIR}/my_math_lib)

# ================ sub dirs
add_subdirectory(my_math_lib)

# ================ exes
add_executable(main main.cpp)
target_link_libraries(main my_sqrt_lib)

