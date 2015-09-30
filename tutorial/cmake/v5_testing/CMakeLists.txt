cmake_minimum_required (VERSION 2.8)
project(cmake_tutorial)

# ================ compiler
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

# ================ options
option(USE_MYSQRT "use my very usefull O(1) sqrt implementation" ON)

# ================ config
configure_file(
    ${PROJECT_SOURCE_DIR}/tutorial_config.hpp.in
    ${PROJECT_SOURCE_DIR}/tutorial_config.hpp
    )

enable_testing()

# ================ include dirs
include_directories(${PROJECT_SOURCE_DIR}) #for tutorial_config.hpp

# ================ sub dirs
if(USE_MYSQRT)
    include_directories(${PROJECT_SOURCE_DIR}/my_math_lib)
    add_subdirectory(my_math_lib)
    set(EXTRA_LIBS ${EXTRA_LIBS} my_sqrt_lib) #push_back
endif(USE_MYSQRT)

add_subdirectory(test)

# ================ exes
add_executable(main main.cpp)
target_link_libraries(main ${EXTRA_LIBS}) #extra_lib can be empty

# ================ install
install(TARGETS main DESTINATION bin)
install(FILES ${PROJECT_SOURCE_DIR}/tutorial_config.hpp DESTINATION include)

# ================ testing
add_test(main_test main) # if return != 0 -> fail

