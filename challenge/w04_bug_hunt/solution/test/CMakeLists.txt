# ================ unit tests
file(GLOB UNIT_TESTS "./" "*.cpp")

add_executable(main_test ${UNIT_TESTS})
target_link_libraries(main_test ${LIB})
