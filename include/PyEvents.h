
/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2017 Antonio Augusto Alves Junior
 *
 *
 *   This file is part of Hydra.Python Analysis Framework.
 *
 *   Hydra is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * PyRandom.h
 *
 *  Created on: 4 August 2017
 *      Author: Deepanshu
 */

/*
 * @file
 *
 * @ingroup
 *
 * @brief
 *
 * @todo
 *
 */
#ifndef PYEVENTS_H_
#define PYEVENTS_H_
#include <add_object.h>
#include <casters.h>
#include <hydra/Events.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <typedefs.h>
#include <string>

/*
 hydra::Events<N, hydra::BACKEND::sys_t>::value_type   \
			     v = e[idx];                                       \
			 return v;                                             \

 */

namespace py = pybind11;

namespace hydra_python {

#define EVENTS_CLASS_BODY(N, BACKEND, BACKEND2)                                \
	py::class_<hydra::Events<N, hydra::BACKEND::sys_t>>(                   \
	    m, #BACKEND "_events_" #N)                                           \
	    .def(py::init<>(), "Zero state Event object")                      \
	    .def(py::init<hydra::GLong_t>(), #N " particle events object")     \
	    .def(py::init<hydra::Events<N, hydra::BACKEND::sys_t>>(),          \
		 "Copy construct from the " #BACKEND " Event object")          \
	    .def(py::init<hydra::Events<N, hydra::BACKEND2::sys_t>>(),         \
		 "Copy construct from the " #BACKEND2 " Event object")         \
	    .def("assign",                                                     \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    const hydra::Events<N, hydra::BACKEND::sys_t>& other) {    \
			 e = other;                                            \
		 }, #BACKEND "_events_"#N##_a,                                                           \
		 "Assign one " #BACKEND " Event object into another " #BACKEND \
		 " Event object.")                                             \
	    .def("assign",                                                     \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::Events<N, hydra::BACKEND2::sys_t>& other) {         \
			 e = other;                                            \
		 }, #BACKEND2 "_events_"#N##_a,                                                           \
		 "Assign " #BACKEND2 " Events object into " #BACKEND           \
		 " Event object.")                                             \
	    .def("GetMaxWeight",                                               \
		 &hydra::Events<N, hydra::BACKEND::sys_t>::GetMaxWeight,       \
		 "Get the Maximum particle weight.")                           \
	    .def("GetNEvents",                                                 \
		 &hydra::Events<N, hydra::BACKEND::sys_t>::GetNEvents,         \
		 "Get the Number of Events N.")                                \
	    .def("Flags",                                                      \
		 [](const hydra::Events<N, hydra::BACKEND::sys_t>& e) {        \
			 typedef decltype(e.FlagsBegin()) iter_t;              \
			 return py::make_iterator<                             \
			     py::return_value_policy::reference_internal,      \
			     iter_t, iter_t, typename iter_t::value_type>(     \
			     e.FlagsBegin(), e.FlagsEnd());                    \
		 },                                                            \
		 "Get the flags iterator.")                                    \
	    .def("Weights",                                                    \
		 [](const hydra::Events<N, hydra::BACKEND::sys_t>& e) {        \
			 typedef decltype(e.WeightsBegin()) iter_t;            \
			 return py::make_iterator<                             \
			     py::return_value_policy::reference_internal,      \
			     iter_t, iter_t, typename iter_t::value_type>(     \
			     e.WeightsBegin(), e.WeightsEnd());                \
		 },                                                            \
		 "Particle weights iterator.")                                 \
	    .def("Daughters",                                                  \
		 [](const hydra::Events<N, hydra::BACKEND::sys_t>& e,          \
		    hydra::GInt_t idx) {                                       \
			 typedef decltype(e.DaughtersBegin(idx)) iter_t;       \
			 return py::make_iterator<                             \
			     py::return_value_policy::reference_internal,      \
			     iter_t, iter_t, typename iter_t::value_type>(     \
			     e.DaughtersBegin(idx), e.DaughtersEnd(idx));      \
		 }, "idx"_a,                                                           \
		 "Daughter iterator. Iterate over the all N events of given "  \
		 "particle idx.")                                                   \
	    .def("Events",                                                     \
		 [](const hydra::Events<N, hydra::BACKEND::sys_t>& e) {        \
			 typedef decltype(e.begin()) iter_t;                   \
			 return py::make_iterator<                             \
			     py::return_value_policy::reference_internal,      \
			     iter_t, iter_t, typename iter_t::value_type>(     \
			     e.begin(), e.end());                              \
		 },                                                            \
		 "Events iterator. Iterate over the all N events of given "    \
		 "particle")                                                   \
	    .def("__getitem__",                                                \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx) {                                       \
			 typedef decltype(e[idx]) iter_t;                      \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 return (hydra::Events<                                \
				 N, hydra::BACKEND::sys_t>::value_type)e[idx]; \
		 }, "idx"_a)                                                            \
	    .def("SetMaxWeight",                                               \
		 &hydra::Events<N, hydra::BACKEND::sys_t>::SetMaxWeight, "weight"_a,       \
		 "Set the maximum weight.")                                    \
	    .def("capacity",                                                   \
		 &hydra::Events<N, hydra::BACKEND::sys_t>::capacity)           \
	    .def("resize", &hydra::Events<N, hydra::BACKEND::sys_t>::resize,   \
		 "Resize the number of Events.")                               \
	    .def("unweight",                                                   \
		 &hydra::Events<N, hydra::BACKEND::sys_t>::Unweight,           \
		 "Unweight all Events with seed.")                             \
	    .def("size", &hydra::Events<N, hydra::BACKEND::sys_t>::size)       \
	    .def("setFlag",                                                    \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx, bool value) {                           \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 auto start = e.FlagsBegin();                          \
			 start[idx] = value;                                   \
		 }, "idx"_a, "flag"_a,                                                           \
		 "Set the ith event flag.")                                    \
	    .def("setWeight",                                                  \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx, hydra::GReal_t value) {                 \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 auto start = e.WeightsBegin();                        \
			 start[idx] = value;                                   \
		 }, "idx"_a, "weight"_a,                                                           \
		 "Set the ith event's weight.")                                \
	    .def("getFlag",                                                    \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx) {                                       \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 auto start = e.FlagsBegin();                          \
			 return (bool)start[idx];                              \
		 }, "idx"_a,                                                           \
		 "get the ith event's flag.")                                  \
	    .def("getWeight",                                                  \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx) {                                       \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 auto start = e.WeightsBegin();                        \
			 return (hydra::GReal_t)start[idx];                    \
		 }, "idx"_a,                                                           \
		 "get the ith event's weight.");

template <>
void add_object<hydra::Events<4, hydra::host::sys_t>>(pybind11::module& m) {
	using namespace pybind11::literals;
	EVENTS_CLASS_BODY(1, host, device);
	EVENTS_CLASS_BODY(2, host, device);
	EVENTS_CLASS_BODY(3, host, device);
	EVENTS_CLASS_BODY(4, host, device);
	EVENTS_CLASS_BODY(5, host, device);
	EVENTS_CLASS_BODY(6, host, device);
	EVENTS_CLASS_BODY(7, host, device);
	EVENTS_CLASS_BODY(8, host, device);
	EVENTS_CLASS_BODY(9, host, device);
	EVENTS_CLASS_BODY(10, host, device);

	EVENTS_CLASS_BODY(1, device, host);
	EVENTS_CLASS_BODY(2, device, host);
	EVENTS_CLASS_BODY(3, device, host);
	EVENTS_CLASS_BODY(4, device, host);
	EVENTS_CLASS_BODY(5, device, host);
	EVENTS_CLASS_BODY(6, device, host);
	EVENTS_CLASS_BODY(7, device, host);
	EVENTS_CLASS_BODY(8, device, host);
	EVENTS_CLASS_BODY(9, device, host);
	EVENTS_CLASS_BODY(10, device, host);
}
}

#endif /* PYEVENTS_H_ */
