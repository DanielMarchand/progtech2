add_library(my_sqrt_lib my_sqrt.cpp)

install(TARGETS my_sqrt_lib DESTINATION bin)
install(FILES my_sqrt.hpp DESTINATION include)
