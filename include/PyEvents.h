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
#include <hydra/Events.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <add_object.h>
#include <typedefs.h>

namespace py = pybind11;

namespace hydra_python {
template<>
void add_object<hydra::Events<4, hydra::host::sys_t> >(pybind11::module& m) {

    py::class_<hydra::Events<4, hydra::host::sys_t > >(m, "Events")
    .def(py::init<>(), "Zero state Event object")
    .def(py::init< hydra::GLong_t > (), "N partical events object")
    .def(py::init< hydra::Events<4, hydra::device::sys_t> >(),
    "Copy construct from the host Event object")

    .def(py::init< hydra::Events<4, hydra::host::sys_t> >(),
    "Copy construct from the device Event object")

    .def("assign", [](hydra::Events<4, hydra::host::sys_t>& e,
                            const hydra::Events<4, hydra::host::sys_t>& other){
        e = other;
    }, "Assign one host Event object into another host Event object.")

    .def("assign", [](hydra::Events<4, hydra::host::sys_t>& e,
                            hydra::Events<4, hydra::device::sys_t>& other){
        e = other;
    }, "Assign device Event object into host Event object.")

    .def("GetMaxWeight", &hydra::Events<4, hydra::host::sys_t>::GetMaxWeight,
    "Get the Maximum particle weight.")

    .def("GetNEvents", &hydra::Events<4, hydra::host::sys_t>::GetNEvents,
    "Get the Number of Events N.")

    .def("Flags", [](const hydra::Events<4, hydra::host::sys_t>& e){
        return py::make_iterator(e.FlagsBegin(), e.FlagsEnd());
    }, py::keep_alive<0, 1>(), "Get the flags iterator.")

    .def("Weights", [](const hydra::Events<4, hydra::host::sys_t>& e) {
        return py::make_iterator(e.WeightsBegin(), e.WeightsEnd());
    }, py::keep_alive<0, 1>(), "Partical weights iterator.")

    .def("Daughters", [](const hydra::Events<4, hydra::host::sys_t>& e, hydra::GInt_t idx) {
        return py::make_iterator(e.DaughtersBegin(idx), e.DaughtersEnd(idx));
    }, py::keep_alive<0, 1>(), "Daughter itertator. Iterate over the all N events of given partical")

    .def("SetMaxWeight", &hydra::Events<4, hydra::host::sys_t>::SetMaxWeight,
    "Set the maximum weight.")

    .def("get", [](hydra::Events<4, hydra::host::sys_t>& e, hydra::GInt_t idx){
        if (idx >= e.size())
            throw py::index_error("list index out of range");
        return e[idx];
    }, "Get the ith event state of all the particles and weight.")

//    .def("begin", [](const hydra::Events<4, hydra::host::sys_t>& e) {
//        return py::make_iterator(e.begin(), e.end());
//    }, py::keep_alive<0, 1>())

    .def("capacity", &hydra::Events<4, hydra::host::sys_t>::capacity)
    .def("resize", &hydra::Events<4, hydra::host::sys_t>::resize, "Resize the number of Events.")
    .def("unweight", &hydra::Events<4, hydra::host::sys_t>::Unweight, "Unweight all Events with seed.")
    .def("size", &hydra::Events<4, hydra::host::sys_t>::size)
    .def("setFlag", [](hydra::Events<4, hydra::host::sys_t>& e, hydra::GInt_t idx, bool value){
        if (idx >= e.size())
            throw py::index_error("list index out of range");
        auto start = e.FlagsBegin();
        start[idx] = value;
    }, "Set the ith event flag.")
    .def("setWeight", [](hydra::Events<4, hydra::host::sys_t>& e, hydra::GInt_t idx, hydra::GReal_t value){
        if (idx >= e.size())
            throw py::index_error("list index out of range");
        auto start = e.WeightsBegin();
        start[idx] = value;
    }, "Set the ith event's weight.")
    ;
}
}

#endif /* PYEVENTS_H_ */
