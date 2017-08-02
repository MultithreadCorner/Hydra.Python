#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "casters.h"
#include "hydra/Events.h"
#include "hydra/Types.h"
#include "thrust/tuple.h"
#include "hydra/host/System.h"
#include <typeinfo>
#include <iostream>
#include <memory>

namespace py = pybind11;

py::tuple foo(const thrust::detail::tuple_of_iterator_references<const double&, const double&, const double&, const double&> iter) {
  return py::make_tuple(thrust::get<0>(iter), thrust::get<1>(iter), thrust::get<2>(iter), thrust::get<3>(iter));
}

PYBIND11_MODULE(HydraPython, m) {
  const int N = 3;
  py::class_< hydra::Events<N, hydra::host::sys_t> >(m, "Events")
    .def(py::init<>())
    .def(py::init< hydra::GLong_t > ())
    .def(py::init< hydra::Events<N, hydra::host::sys_t> >())
    .def("__getitem__", [](const hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx) {
	auto it = e.begin() + idx;
	/*TODO: Here I need to make a template function for variable number of arguments
	 * Say for N=4 we will have first tuple with 1 + 4 elements. [get<0>, get<1>, get<2>, get<3>, get<4>]
	 * but for N=3 we will have first tuple with 1 + 3 elements. [get<0>, get<1>, get<2>, get<3>]
	 * So I need to replace this call with a template function to automate this process and I can do
	 * that with TMP because the number N is fix.
	 */
	auto first = *it;
	auto first_first = thrust::get<0>(first);
	auto first_second = thrust::get<1>(first);
	//return first_second;
	//auto first_second_first = thrust::get<0>(first_second);
	//auto first_second_second = thrust::get<1>(first_second);
	//auto first_second_third = thrust::get<2>(first_second);
	//auto first_second_fourth = thrust::get<3>(first_second);
	return foo(first_second);
      }, py::is_operator())
    .def("__setitem", [](hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx, hydra::GReal_t item){
	// ???????????????????
      }, py::is_operator())
    .def("getFlag", [](const hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx){
	auto i = e.FlagsBegin() + idx;
	std::cout << std::boolalpha << *(i + idx) << std::endl;
	})
    .def("setFlag", [](hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx, bool flag) {
	auto i = e.FlagsBegin() + idx;
	*(i + idx) = flag;
      })
    .def("getWeight", [](const hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx){
	auto i = e.WeightsBegin();
	std::cout << *(i + idx) << std::endl;
      })
    .def("setWeight", [](hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx, hydra::GReal_t value) {
	auto i = e.WeightsBegin();
	*(i + idx) = value;
      })
    .def("getDaughter", [](const hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx) {
	auto i = e.DaughtersBegin(idx);
	return py::make_tuple(thrust::get<0>(*i), thrust::get<1>(*i), thrust::get<2>(*i), thrust::get<3>(*i));
      })
    .def("setDaughter", [](hydra::Events<N, hydra::host::sys_t>& e, hydra::GUInt_t idx, std::vector<hydra::GReal_t>& value) {
	auto i = e.DaughtersBegin(idx);
	if (value.size() != 4)
	  throw py::type_error("List  argument does not contain exactly 4 values!");
	thrust::get<0>(*i) = value[0];
       	thrust::get<1>(*i) = value[1];
	thrust::get<2>(*i) = value[2];
	thrust::get<3>(*i) = value[3];	
      })
    ;
}
