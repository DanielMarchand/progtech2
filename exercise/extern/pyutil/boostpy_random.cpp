#include <boost/python.hpp>
#include "../include/util/random.hpp"
#include <iostream>

using namespace boost::python;

namespace detail {

    using int_mt_rng = util::rng_class<int>;
    using double_mt_rng = util::rng_class<double>;

    BOOST_PYTHON_MODULE_INIT(boostpy_random) {
        class_<int_mt_rng> ir ("int_rng", init<int, int>());
            ir.def("__call__", &int_mt_rng::operator());

            uint64_t const & (int_mt_rng::*fp1i)() = &int_mt_rng::seed;
            ir.def("seed", fp1i, return_value_policy<copy_const_reference>());

            void (int_mt_rng::*fp2i)(uint64_t const &) = &int_mt_rng::seed;
            ir.def("seed", fp2i);

            ir.def("set_range", &int_mt_rng::set_range);

        class_<double_mt_rng> dr ("float_rng", init<double, double>());
            dr.def("__call__", &double_mt_rng::operator());

            uint64_t const & (double_mt_rng::*fp1d)() = &double_mt_rng::seed;
            dr.def("seed", fp1d, return_value_policy<copy_const_reference>());

            void (double_mt_rng::*fp2d)(uint64_t const &) = &double_mt_rng::seed;
            dr.def("seed", fp2d);
    
            dr.def("set_range", &double_mt_rng::set_range);

        void (*fp1f)(uint64_t const &) = &util::seed<>;
        def("seed", fp1f);

        uint64_t (*fp2f)() = &util::seed<>;
        def("seed", fp2f);
    }

}
