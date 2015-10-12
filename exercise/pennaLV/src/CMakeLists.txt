# ================ sub dirs
add_subdirectory(zoo)

# ================ exes
add_executable(main main.cpp)
target_link_libraries(main ${LIB})
