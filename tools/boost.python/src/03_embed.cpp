/*******************************************************************************
 *
 * Boost Python Embedding Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * Licensed under the Apache License: http://www.apache.org/licenses/LICENSE-2.0
 * 
 ******************************************************************************/

#include <boost/python.hpp>

boost::python::str pycode = "         \n\
a,b,x=0,1,''                          \n\
while b<99:x+=' '+str(b);a,b=b,a+b    \n\
";

boost::python::str pycode2 = "\
print(x)\
";

using namespace boost::python;

int main( int argc, char ** argv ) {

  try {

    Py_Initialize();
    object main_module = import("__main__");     // can import any module
    object main_namespace = main_module.attr("__dict__");

    object dummy = exec(pycode, main_namespace); // run pycode in main namespace
                 //exec_file to run a script

    // std::string x = main_namespace["x"];      // doesn't work, what is x?
    object x = main_namespace["x"];
    std::cout << extract<char*>(x) << std::endl; // type infusion

    main_namespace["x"] = "gone";
    dummy = exec(pycode2, main_namespace);       // check x in main namespace


  } catch(error_already_set) {
    PyErr_Print();
  }
  return 0;

}
