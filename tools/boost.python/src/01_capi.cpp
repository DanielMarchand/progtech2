/*******************************************************************************
 *
 * Simple Python Extension Example
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * Licensed under the Apache License: http://www.apache.org/licenses/LICENSE-2.0
 * 
 ******************************************************************************/

#include <Python.h> // must go first, because it defines some preprocessor directives
#include <iostream>

// Our work function is a Python object (like everything else)
static PyObject *
fibo(PyObject *self, PyObject *args) {

    int max;
    if(!PyArg_ParseTuple(args, "i", &max))
        return NULL;

    int a = 0, b = 1;
    std::string s = "0 1";

    // Compute the Fibonacci sequence
    while((b+=a^=b^=a^=b)<=max)s+=' '+std::to_string(b);

    return Py_BuildValue("s", s.c_str());

}

// Print the Python path directly from here
static PyObject *
pbin(PyObject *self, PyObject *args) {

    std::cout << Py_GetProgramFullPath() << std::endl;
    Py_RETURN_NONE;

}

// Advertising exported functions in this array
static PyMethodDef methods[] = {

    // name     , impl, param list  ,
    // docstring
    {"fibonacci", fibo, METH_VARARGS,
     "Return Fibonacci sequence up to provided maximum value >= 1."},

    {"print_bin", pbin, METH_NOARGS,
     "Print the path of the Python binary."},

    {NULL, NULL, 0, NULL}  // sentinel

};

// Upon importing XXX from XXX.so the parser requires initXXX
PyMODINIT_FUNC
initfib(void) {
    (void) Py_InitModule("fib", methods);
}





extern "C" void stray_function(char * c) {
    std::cout << "hello " << c << std::endl;
}
