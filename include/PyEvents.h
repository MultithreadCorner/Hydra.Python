/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2017 Deepanshu Thakur
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
#include <hydra/Events.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <typedefs.h>
#include <string>

namespace py = pybind11;

namespace hydra_python {

#define EVENTS_CLASS_BODY(N, BACKEND, BACKEND2)                                \
	py::class_<hydra::Events<N, hydra::BACKEND::sys_t> >(                  \
	    m, #BACKEND "Events" #N)                                           \
	    .def(py::init<>(), "Zero state Event object")                      \
	    .def(py::init<hydra::GLong_t>(), #N " particle events object")     \
	    .def(py::init<hydra::Events<N, hydra::BACKEND::sys_t> >(),         \
		 "Copy construct from the " #BACKEND " Event object")          \
	    .def(py::init<hydra::Events<N, hydra::BACKEND2::sys_t> >(),        \
		 "Copy construct from the " #BACKEND2 " Event object")         \
	    .def("assign",                                                     \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    const hydra::Events<N, hydra::BACKEND::sys_t>& other) {    \
			 e = other;                                            \
		 },                                                            \
		 "Assign one " #BACKEND " Event object into another " #BACKEND \
		 " Event object.")                                             \
	    .def("assign",                                                     \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::Events<N, hydra::BACKEND2::sys_t>& other) {         \
			 e = other;                                            \
		 },                                                            \
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
			 return py::make_iterator(e.FlagsBegin(),              \
						  e.FlagsEnd());               \
		 },                                                            \
		 py::keep_alive<0, 1>(), "Get the flags iterator.")            \
	    .def("Weights",                                                    \
		 [](const hydra::Events<N, hydra::BACKEND::sys_t>& e) {        \
			 return py::make_iterator(e.WeightsBegin(),            \
						  e.WeightsEnd());             \
		 },                                                            \
		 py::keep_alive<0, 1>(), "Particle weights iterator.")         \
	    .def("Daughters",                                                  \
		 [](const hydra::Events<N, hydra::BACKEND::sys_t>& e,          \
		    hydra::GInt_t idx) {                                       \
			 return py::make_iterator(e.DaughtersBegin(idx),       \
						  e.DaughtersEnd(idx));        \
		 },                                                            \
		 py::keep_alive<0, 1>(),                                       \
		 "Daughter iterator. Iterate over the all N events of given "  \
		 "particle")                                                   \
	    .def("SetMaxWeight",                                               \
		 &hydra::Events<N, hydra::BACKEND::sys_t>::SetMaxWeight,       \
		 "Set the maximum weight.")                                    \
	    .def("__getitem__",                                                \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx) {                                       \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 return e[idx];                                        \
		 },                                                            \
		 py::is_operator(),                                            \
		 "Get the ith event state of all the particles and weight.")   \
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
		 },                                                            \
		 "Set the ith event flag.")                                    \
	    .def("setWeight",                                                  \
		 [](hydra::Events<N, hydra::BACKEND::sys_t>& e,                \
		    hydra::GInt_t idx, hydra::GReal_t value) {                 \
			 if (idx >= e.size())                                  \
				 throw py::index_error(                        \
				     "list index out of range");               \
			 auto start = e.WeightsBegin();                        \
			 start[idx] = value;                                   \
		 },                                                            \
		 "Set the ith event's weight.");

template <>
void add_object<hydra::Events<4, hydra::host::sys_t> >(pybind11::module& m) {
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

	py::class_<hydra::Events<3, hydra::device::sys_t> >(m, "Events")
	    .def(py::init<>(), "Zero state Event object")
	    .def(py::init<hydra::GLong_t>(), " partical events object")
	    .def(py::init<hydra::Events<3, hydra::device::sys_t> >())
	    .def(py::init<hydra::Events<3, hydra::host::sys_t> >())
		.def("assign", [](hydra::Events<3, hydra::device::sys_t>& e,
		    const hydra::Events<3, hydra::device::sys_t>& other) {
			 e = other;
		}, "Assign one device Event object into another Event object.")
	    .def("assign", [](hydra::Events<3, hydra::device::sys_t>& e,
		    hydra::Events<3, hydra::host::sys_t>& other) {
			 e = other;
		 }, "Assign Events object into Event object.")
		.def("GetMaxWeight", &hydra::Events<3, hydra::device::sys_t>::GetMaxWeight)
	    .def("GetNEvents", &hydra::Events<3, hydra::device::sys_t>::GetNEvents)
		.def("SetMaxWeight", &hydra::Events<3, hydra::device::sys_t>::SetMaxWeight, "Set the maximum weight.")

//**********************************ERROR WITH DEVICE****************************************//
//		.def("Flags", [](const hydra::Events<3, hydra::device::sys_t>& e) {
//			 return py::make_iterator(e.FlagsBegin(), e.FlagsEnd());
//		 }, py::keep_alive<0, 1>(), "Get the flags iterator.")
		.def("Flags", [](const hydra::Events<3, hydra::device::sys_t>& e) {
			 return e.FlagsBegin();
		 }, "Get the flags iterator.")
//		.def("Weights", [](const hydra::Events<3, hydra::device::sys_t>& e) {
//			 return py::make_iterator(e.WeightsBegin(), e.WeightsEnd());
//		 }, py::keep_alive<0, 1>(), "Particle weights iterator.")
//	    .def("Daughters", [](const hydra::Events<3, hydra::device::sys_t>& e, hydra::GInt_t idx) {
//			 return py::make_iterator(e.DaughtersBegin(idx),
//						  e.DaughtersEnd(idx));
//		 }, py::keep_alive<0, 1>(), "Daughter iterator. Iterate over the all N events of given particle")
//		.def("__getitem__", [](hydra::Events<3, hydra::device::sys_t>& e, hydra::GInt_t idx) {
//			 if (idx >= e.size())
//				 throw py::index_error("list index out of range");
//			 return e[idx];
//		 }, py::is_operator(), "Get the ith event state of all the particles and weight.")

		.def("capacity", &hydra::Events<3, hydra::device::sys_t>::capacity)
	    .def("resize", &hydra::Events<3, hydra::device::sys_t>::resize, "Resize the number of Events.")
	    .def("unweight", &hydra::Events<3, hydra::device::sys_t>::Unweight, "Unweight all Events with seed.")
	    .def("size", &hydra::Events<3, hydra::device::sys_t>::size)
		.def("setFlag", [](hydra::Events<3, hydra::device::sys_t>& e, hydra::GInt_t idx, bool value) {
			if (idx >= e.size())
				throw py::index_error("list index out of range");
			 auto start = e.FlagsBegin();
			 start[idx] = value;
		 }, "Set the ith event flag.")
	    .def("setWeight", [](hydra::Events<3, hydra::device::sys_t>& e, hydra::GInt_t idx, hydra::GReal_t value) {
			if (idx >= e.size())
				throw py::index_error("list index out of range");
			 auto start = e.WeightsBegin();
			 start[idx] = value;
		 }, "Set the ith event's weight.")
		;

	//    EVENTS_CLASS_BODY(1,device,host);
	//    EVENTS_CLASS_BODY(2,device,host);
	//    EVENTS_CLASS_BODY(3,device,host);
	//    EVENTS_CLASS_BODY(4,device,host);
	//    EVENTS_CLASS_BODY(5,device,host);
	//    EVENTS_CLASS_BODY(6,device,host);
	//    EVENTS_CLASS_BODY(7,device,host);
	//    EVENTS_CLASS_BODY(8,device,host);
	//    EVENTS_CLASS_BODY(9,device,host);
	//    EVENTS_CLASS_BODY(10,device,host);

	//    py::class_<hydra::Events<4, hydra::host::sys_t > >(m, "Events")
	//    .def(py::init<>(), "Zero state Event object")
	//    .def(py::init< hydra::GLong_t > (), "N partical events object")
	//    .def(py::init< hydra::Events<4, hydra::device::sys_t> >(),
	//    "Copy construct from the device Event object")
	//
	//    .def(py::init< hydra::Events<4, hydra::host::sys_t> >(),
	//    "Copy construct from the host Event object")
	//
	//    .def("assign", [](hydra::Events<4, hydra::host::sys_t>& e,
	//                            const hydra::Events<4,
	//                            hydra::host::sys_t>& other){
	//        e = other;
	//    }, "Assign one host Event object into another host Event object.")
	//
	//    .def("assign", [](hydra::Events<4, hydra::host::sys_t>& e,
	//                            hydra::Events<4, hydra::device::sys_t>&
	//                            other){
	//        e = other;
	//    }, "Assign device Event object into host Event object.")
	//
	//    .def("GetMaxWeight", &hydra::Events<4,
	//    hydra::host::sys_t>::GetMaxWeight,
	//    "Get the Maximum particle weight.")
	//
	//    .def("GetNEvents", &hydra::Events<4,
	//    hydra::host::sys_t>::GetNEvents,
	//    "Get the Number of Events N.")
	//
	//    .def("Flags", [](const hydra::Events<4, hydra::host::sys_t>& e){
	//        return py::make_iterator(e.FlagsBegin(), e.FlagsEnd());
	//    }, py::keep_alive<0, 1>(), "Get the flags iterator.")
	//
	//    .def("Weights", [](const hydra::Events<4, hydra::host::sys_t>& e)
	//    {
	//        return py::make_iterator(e.WeightsBegin(), e.WeightsEnd());
	//    }, py::keep_alive<0, 1>(), "Partical weights iterator.")
	//
	//    .def("Daughters", [](const hydra::Events<4, hydra::host::sys_t>&
	//    e, hydra::GInt_t idx) {
	//        return py::make_iterator(e.DaughtersBegin(idx),
	//        e.DaughtersEnd(idx));
	//    }, py::keep_alive<0, 1>(), "Daughter itertator. Iterate over the
	//    all N events of given partical")
	//
	//    .def("SetMaxWeight", &hydra::Events<4,
	//    hydra::host::sys_t>::SetMaxWeight,
	//    "Set the maximum weight.")
	//
	//    .def("__getitem__", [](hydra::Events<4, hydra::host::sys_t>& e,
	//    hydra::GInt_t idx){
	//        if (idx >= e.size())
	//            throw py::index_error("list index out of range");
	//        return e[idx];
	//    }, py::is_operator(), "Get the ith event state of all the
	//    particles and weight.")
	//
	////    .def("begin", [](const hydra::Events<4, hydra::host::sys_t>& e)
	///{
	////        return py::make_iterator(e.begin(), e.end());
	////    }, py::keep_alive<0, 1>())
	//
	//    .def("capacity", &hydra::Events<4, hydra::host::sys_t>::capacity)
	//    .def("resize", &hydra::Events<4, hydra::host::sys_t>::resize,
	//    "Resize the number of Events.")
	//    .def("unweight", &hydra::Events<4, hydra::host::sys_t>::Unweight,
	//    "Unweight all Events with seed.")
	//    .def("size", &hydra::Events<4, hydra::host::sys_t>::size)
	//    .def("setFlag", [](hydra::Events<4, hydra::host::sys_t>& e,
	//    hydra::GInt_t idx, bool value){
	//        if (idx >= e.size())
	//            throw py::index_error("list index out of range");
	//        auto start = e.FlagsBegin();
	//        start[idx] = value;
	//    }, "Set the ith event flag.")
	//    .def("setWeight", [](hydra::Events<4, hydra::host::sys_t>& e,
	//    hydra::GInt_t idx, hydra::GReal_t value){
	//        if (idx >= e.size())
	//            throw py::index_error("list index out of range");
	//        auto start = e.WeightsBegin();
	//        start[idx] = value;
	//    }, "Set the ith event's weight.")
	//    ;
}
}

#endif /* PYEVENTS_H_ */
