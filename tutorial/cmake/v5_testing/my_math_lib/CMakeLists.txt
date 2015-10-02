add_library(my_sqrt_lib my_sqrt.cpp)

install(TARGETS my_sqrt_lib DESTINATION bin)
install(FILES my_sqrt.hpp DESTINATION include)
install(FILES ${PROJECT_SOURCE_DIR}/tutorial_config.hpp DESTINATION include)
