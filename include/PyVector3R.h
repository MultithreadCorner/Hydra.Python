
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
 * Vector.cpp
 *
 *  Created on: Aug 4, 2017
 *      Author: Deepanshu Thakur
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
#ifndef PYVECTOR3R_H_
#define PYVECTOR3R_H_
#include <pybind11/pybind11.h>
#include "hydra/Vector3R.h"
#include "hydra/Types.h"
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <sstream>

namespace py = pybind11;

namespace hydra_python {
template<>
void add_object<hydra::Vector3R>(pybind11::module &m) {
    py::class_<hydra::Vector3R>(m, "Vector3R")
        .def(py::init<>())
        .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t>())
        .def(py::init<hydra::Vector3R>())
        .def("__init__", [](hydra::Vector3R &vec, std::vector <hydra::GReal_t> &lst) {
            if (lst.size() == 3) {
                vec = hydra::Vector3R();
                for (int i = 0; i < 3; ++i)
                    vec.set(i, lst[i]);
                return;
            }
            throw pybind11::type_error("list argument does not contain exactly 3 values!");
        })
        .def("__imul__", &hydra::Vector3R::operator*=)
        .def("__itruediv__", &hydra::Vector3R::operator/=)
        .def("assign", [](hydra::Vector3R &v, const hydra::Vector3R &other) { v = other; })
        .def("__iadd__", &hydra::Vector3R::operator+=)
        .def("__isub__", &hydra::Vector3R::operator-=)
        .def("set", (void (hydra::Vector3R::*)(hydra::GInt_t, hydra::GReal_t)) &hydra::Vector3R::set)
        .def("set", (void (hydra::Vector3R::*)(hydra::GReal_t, hydra::GReal_t, hydra::GReal_t)) &hydra::Vector3R::set)
        .def("applyRotateEuler", &hydra::Vector3R::applyRotateEuler)
        .def("get", &hydra::Vector3R::get)
        .def("dot", &hydra::Vector3R::dot)
        .def("d3mag", &hydra::Vector3R::d3mag)
        .def("swap", &hydra::Vector3R::swap)
        .def("swap", [](hydra::Vector3R &v, hydra::Vector3R &other){ swap(v, other); })
        .def("cross", [](const hydra::Vector3R &v, const hydra::Vector3R &other){ return cross(v, other); })
//        .def("rotateEuler", [](const hydra::Vector3R &v, hydra::GReal_t phi, hydra::GReal_t theta, hydra::GReal_t ksi) {
//            return rotateEuler(v, phi, theta, ksi);
//        })
        .def("__repr__", [](const hydra::Vector3R &e) {
            std::stringstream ss;
            ss << e;
            return ss.str();
        })
        .def(hydra::GReal_t() * py::self)
        .def(py::self * hydra::GReal_t())
        .def(py::self * hydra::Vector3R())
        .def(py::self / hydra::GReal_t())
        .def(py::self + hydra::Vector3R())
        .def(py::self - hydra::Vector3R())
        .def("__eq__", [](const hydra::Vector3R &one, const hydra::Vector3R &two) {
            for (auto i = 0; i < 3; ++i)
                if (one.get(i) != two.get(i))
                    return false;
            return true;
        }, py::is_operator())
        .def("__ne__", [](const hydra::Vector3R &one, const hydra::Vector3R &two) {
            for (auto i = 0; i < 3; ++i)
                if (one.get(i) != two.get(i))
                    return true;
            return false;
        }, py::is_operator())
        .def("__getitem__", [](hydra::Vector3R &obj, hydra::GInt_t idx) {
            return obj.get(idx);
        }, py::is_operator())
        .def("__setitem__", [](hydra::Vector3R &obj, hydra::GInt_t idx, hydra::GReal_t value) {
            return obj.set(idx, value);
        }, py::is_operator());
}
}
#endif //PYVECTOR3R_H_
