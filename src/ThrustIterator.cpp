#include <pybind11/pybind11.h>
#include "Events.h"
#include "hydra/Types.h"
#include "hydra/Vector4R.h"
#include <thrust/iterator/iterator_adaptor.h>
#include <thrust/iterator/detail/is_trivial_iterator.h>
#include <thrust/detail/type_traits.h>
#include <iostream>
#include <memory>


namespace py = pybind11;

PYBIND11_MODULE(ThrustIterator, m) {
    py::class_< thrust::detail::normal_iterator<thrust::device_ptr<bool> > >(m, "ThrustIterator")
        .def(py::init<>())
        .def(py::init <thrust::device_ptr<bool> > ())
    ;
    py::class_< thrust::zip_iterator<thrust::tuple<thrust::detail::normal_iterator<thrust::device_ptr<double> >, thrust::detail::normal_iterator<thrust::device_ptr<hydra::Vector4R> >, thrust::detail::normal_iterator<thrust::device_ptr<hydra::Vector4R> >, thrust::detail::normal_iterator<thrust::device_ptr<hydra::Vector4R> > > >> (m, "ThrustZipIterator")
        .def(py::init<>())
    ;
    py::class_< hydra::Vector4R > (m, "Vector4R")
        .def(py::init<>())
        .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t, hydra::GReal_t>())
    ;
}