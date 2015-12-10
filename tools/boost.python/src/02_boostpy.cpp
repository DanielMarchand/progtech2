/*******************************************************************************
 *
 * Boost Python Extension Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * Licensed under the Apache License: http://www.apache.org/licenses/LICENSE-2.0
 * 
 ******************************************************************************/

#include <boost/python.hpp>
#include <iostream>

// A normal C++ function
std::string fibo(int max) {

    int a = 0, b = 1;
    std::string s = "0 1";

    // Compute the Fibonacci sequence
    while((b+=a^=b^=a^=b)<=max)s+=' '+std::to_string(b);

    return s;

}

#include <boost/python.hpp>

void pbin() {
    std::cout << Py_GetProgramFullPath() << std::endl;
}

// The following code could simply include the above

// The module must be the same name as the .so
BOOST_PYTHON_MODULE(fibboost) {
    boost::python::def("fibonacci", fibo);
    boost::python::def("print_bin", pbin, "Print the path of the Python binary.");
}
