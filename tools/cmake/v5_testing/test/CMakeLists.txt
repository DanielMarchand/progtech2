# ================ exes
add_executable(real_test test.cpp)
target_link_libraries(real_test ${EXTRA_LIBS})

# ================ testing
add_test(real_test real_test)


