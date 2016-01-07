/*******************************************************************************
 *
 * Boost Python Classes
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * Licensed under the Apache License: http://www.apache.org/licenses/LICENSE-2.0
 * 
 ******************************************************************************/

#include <iostream>
#include <string>

class World {
    public:
    World(const std::string& first, const std::string second) {
        this->first = first;
        this->second = second;
    }
    std::string str() const { return first + " " + second; }
    void set_first(std::string first) { this->first = first; }
    std::string first;
    std::string second;
};

std::string freestr(const World & w) {
    return w.str() + " (free)";
}

/******************************************************************************/

#include "../../../exercise/vtable/veggies_crtp.hpp"
// Since cucumber doesn't provide a std::ostream& overload and
// boost::python::str(self) expects one, let's remedy this:
std::ostream & operator<<(std::ostream & o, const Cucumber & c) {
    c.print();
    return o;
}

/******************************************************************************/

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(cppclass) {

    class_<World>("world", init<std::string, std::string>())
        .def("s1", &World::str)
        .def("s2", freestr)
        .def_readonly("first", &World::first)
        .def_readwrite("second", &World::second)
        .add_property("indirect_first",  &World::first, &World::set_first)
    ;
    def("s3", freestr);

/******************************************************************************/

    using self_ns::str;
    class_<OneDimVegetable<Cucumber>>("cucumber_base");
    class_<Cucumber, bases<OneDimVegetable<Cucumber>> >("cucumber")
        .def("grow", &Cucumber::grow)
        .def("name", &OneDimVegetable<Cucumber>::get_name)
        .def("print_", &OneDimVegetable<Cucumber>::print)
        .def(self += double())                                  // operator+=
        .def(str(self))                                         // operator<<
        .def("__repr__", &OneDimVegetable<Cucumber>::get_name)
    ;

}
