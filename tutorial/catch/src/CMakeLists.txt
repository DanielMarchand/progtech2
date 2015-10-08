# ================ sub dirs
add_subdirectory(prime)

# ================ Unit tests

file(GLOB_RECURSE UnitTests "prime" "*_test.cpp")
add_executable(main_test ${UnitTests} main_test.cpp)
target_link_libraries(main_test ${LIB})

add_test(main_test main_test)
