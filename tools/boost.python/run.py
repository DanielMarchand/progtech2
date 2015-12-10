#!/usr/bin/env python2.7

# C++-Python integration as shown in the lecture.
# Commented lines are too noisy for the whole run: for maximum educational
# value, execute these commands in an interactive Python session line by line.

# Python C-API example
import lib.fib as fib1
print(fib1.fibonacci(999))
fib1.print_bin()
#help(fib1)

# Python ctypes
import ctypes
a = ctypes.CDLL("./lib/fib.so")
#help(a)
print(a.__dict__)
a.stray_function("world?")
print(a.__dict__)            # not very reliable...
#print(a._FuncPtr.__dict__)

# Boost Python
import lib.fibboost as fib2
#help(fib2)
print(fib2.fibonacci(999))
fib2.print_bin()

# Boost Python example class
import lib.cppclass as cppc
#help(cppc)
w = cppc.world("hello", "world!")
print( w.s1() )
w.second = "WORLD!"
print( w.s2() )
#w.first = "hi"
w.indirect_first = "hi"
print( cppc.s3(w) )

# Boost Python cucumbers
c = cppc.cucumber()
print( c.name() )
c.print_()
c.grow(1.5)
print(c)  # both Python print and Cucumber::print() are adding a newline at the end
c += 2
print( str(c) )  # uses the std::ostream& overload, just like print(c)
print( repr(c) )
