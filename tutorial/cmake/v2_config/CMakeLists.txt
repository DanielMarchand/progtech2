cmake_minimum_required (VERSION 2.8)
project(cmake_tutorial)

# ================ compiler
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

# ================ set variables
set(version_major 2)
set(version_minor 0)
set(custom_variable 25)

# ================ config
configure_file(
    ${PROJECT_SOURCE_DIR}/tutorial_config.hpp.in
    ${PROJECT_SOURCE_DIR}/tutorial_config.hpp
    )

# ================ exes
add_executable(main main.cpp)
