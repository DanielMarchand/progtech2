# ================ include dirs
include_directories(sim)

# ================ sub dirs
add_subdirectory(zoo)

# ================ exes
add_executable(main main.cpp)
target_link_libraries(main ${LIB})

# ================ Unit tests

file(GLOB_RECURSE UnitTests "zoo" "*_test.cpp")
add_executable(all_tests ${UnitTests} all_tests.cpp)
target_link_libraries(all_tests ${LIB})

add_test(NAME all_tests COMMAND all_tests)
