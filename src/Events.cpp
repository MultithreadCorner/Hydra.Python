#include <pybind11/pybind11.h>
#include "hydra/Events.h"
#include "hydra/Types.h"
#include "thrust/tuple.h"
#include "hydra/host/System.h"
#include <typeinfo>
#include <iostream>
#include <memory>


namespace py = pybind11;

PYBIND11_MODULE(HydraPython, m) {
  const int N = 3;
  py::class_< hydra::Events<N, hydra::host::sys_t> >(m, "Events")
    .def(py::init<>())
    .def(py::init< hydra::GLong_t > ())
    .def(py::init< hydra::Events<N, hydra::host::sys_t> >())
    .def(py::init< hydra::Events<N, hydra::host::sys_t> >())
    .def("FlagsBegin", [](hydra::Events<N, hydra::host::sys_t>& e){
	auto i = e.FlagsBegin();
	std::cout << std::boolalpha << *i << " " << *(i + 1) << std::endl;
	})
    .def("WeightsBegin", [](hydra::Events<N, hydra::host::sys_t>& e) {
	auto i = e.WeightsBegin();
	std::cout << *i << " " << *(i + 1) << std::endl;
      })
    .def("DaughtersBegin", [](hydra::Events<N, hydra::host::sys_t>& e, hydra::GInt_t a) {
	auto i = e.DaughtersBegin(a);
	std::cout << *i << " " << *(i + 1) << std::endl;
      })
    .def("begin", [](hydra::Events<N, hydra::host::sys_t>&e) {
	auto it = e.begin();
	auto first = *it;
	auto first_first = thrust::get<0>(first);
	auto second = thrust::get<1>(first);
	std::cout << first_first << std::endl;
	std::cout << typeid(first).name() << std::endl;
	for (auto i = second.begin(); i != second.end(); ++i)
	  std::cout << *i << ", ";
	return it;
      })
    ;
}
