
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
 * PyVector4R.h
 *
 *  Created on: Jul 27, 2017
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

#ifndef PYVECTOR4R_H_
#define PYVECTOR4R_H_
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include "hydra/Types.h"
#include "hydra/Vector3R.h"
#include "hydra/Vector4R.h"

namespace py = pybind11;

namespace hydra_python {
template <>
void add_object<hydra::Vector4R>(pybind11::module &m) {
	using namespace pybind11::literals;
	py::class_<hydra::Vector4R>(m, "Vector4R")
	    .def(py::init<>(), "Create object with 0 default value.")
	    .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t,
			  hydra::GReal_t>(), "Create object with 3 float values.")
	    .def(py::init<hydra::Vector4R>(), "Create object with another Vector3R object.")
	    .def(
		"__init__",
		[](hydra::Vector4R &vec, std::array<hydra::GReal_t, 4> &lst) {
			if (lst.size() == 4) {
				vec = hydra::Vector4R();
				for (int i = 0; i < 4; ++i) vec.set(i, lst[i]);
				return;
			}
			throw pybind11::type_error(
			    "list argument does not contain exactly 4 values!");
		}, "Create object with list of 4 float values")
	    .def("set",
		 (void (hydra::Vector4R::*)(hydra::GInt_t, hydra::GReal_t)) &
		     hydra::Vector4R::set, "idx"_a, "value"_a, "Set the ith value with float.")
	    .def("set",
		 (void (hydra::Vector4R::*)(hydra::GReal_t, hydra::GReal_t,
					    hydra::GReal_t, hydra::GReal_t)) &
		     hydra::Vector4R::set, "first_value"_a, "second_value"_a, "third_value"_a, "fourth_value"_a, "Set all 3 values of Vector3R object.")
	    .def("__imul__", &hydra::Vector4R::operator*=, "In place multiply with other float value.")
	    .def("__itruediv__", &hydra::Vector4R::operator/=, "In place divide with other float value.")
	    .def("assign", [](hydra::Vector4R &v,
			      const hydra::Vector4R &other) { v = other; }, "Assign one Vector4R object to other Vector4R object.")
	    .def("__iadd__", &hydra::Vector4R::operator+=, "In place add with other Vector3R object.")
	    .def("__isub__", &hydra::Vector4R::operator-=, "In place subtract with other Vector3R object.")
	    .def("get", &hydra::Vector4R::get, "idx"_a, "Get the value at given index.")
	    .def("cont", &hydra::Vector4R::cont, "vector"_a, "Get cont of two vectors.")
	    .def("mass2", &hydra::Vector4R::mass2, "Get the mass2 of a vector.")
	    .def("mass", &hydra::Vector4R::mass, "Get the mass of a vector.")
	    .def("applyRotateEuler", &hydra::Vector4R::applyRotateEuler, "alpha"_a, "beta"_a, "gamma"_a, "Apply Rotate Euler with given alpha, beta and gamma values.")
	    .def("applyBoostTo",
		 (void (hydra::Vector4R::*)(const hydra::Vector4R &, bool)) &
		     hydra::Vector4R::applyBoostTo,
		 py::arg("Vector4R"), py::arg("inverse") = false)
	    .def("applyBoostTo",
		 (void (hydra::Vector4R::*)(const hydra::Vector3R &, bool)) &
		     hydra::Vector4R::applyBoostTo,
		 py::arg("Vector3R"), py::arg("inverse") = false)
	    .def("applyBoostTo", (void (hydra::Vector4R::*)(
				     const hydra::GReal_t, const hydra::GReal_t,
				     const hydra::GReal_t, bool inverse)) &
				     hydra::Vector4R::applyBoostTo,
		 py::arg("bx"), py::arg("by"), py::arg("bz"),
		 py::arg("inverse") = false)
	    .def("cross", &hydra::Vector4R::cross, "vector"_a, "Cross product of two Vector4R.")
	    .def("dot", &hydra::Vector4R::dot, "vector"_a, "Dot product of two Vector4R.")
	    .def("d3mag", &hydra::Vector4R::d3mag, "3 momentum mag of a vector.")
	    .def("scalartripler3", &hydra::Vector4R::scalartripler3, "Vector4R_1"_a, "Vector4R_2"_a, "Vector4R_3"_a, "Calculate (Vector4R_1xVector4R_2)*Vector4R_3 with calling vector as applyBoostTo argument.")
	    .def("dotr3", &hydra::Vector4R::dotr3, "Vector4R_1"_a, "Vector4R_2"_a, "Calculate the 3-D dot product.")
	    .def("mag2r3", &hydra::Vector4R::mag2r3, "Vector4R"_a, "Calculate the 3-d magnitude squared")
	    .def("magr3", &hydra::Vector4R::magr3, "Vector4R"_a, "Calculate the 3-d magnitude")
	    .def("swap", &hydra::Vector4R::swap, "Vector4R"_a, "Swap two Vector4R")
	    .def("swap", [](hydra::Vector4R &v,
			    hydra::Vector4R &other) { swap(v, other); })
	    .def("__repr__",
		 [](const hydra::Vector4R &e) {
			 std::stringstream ss;
			 ss << e;
			 return ss.str();
		 })
	    .def(hydra::GReal_t() * py::self)
	    .def(py::self * hydra::GReal_t())
	    .def(py::self * hydra::Vector4R())
	    .def(py::self / hydra::GReal_t())
	    .def(py::self + hydra::Vector4R())
	    .def(py::self - hydra::Vector4R())
	    .def("__eq__",
		 [](const hydra::Vector4R &one, const hydra::Vector4R &two) {
			 for (auto i = 0; i < 4; ++i)
				 if (one.get(i) != two.get(i)) return false;
			 return true;
		 },
		 py::is_operator())
	    .def("__ne__",
		 [](const hydra::Vector4R &one, const hydra::Vector4R &two) {
			 for (auto i = 0; i < 4; ++i)
				 if (one.get(i) != two.get(i)) return true;
			 return false;
		 },
		 py::is_operator())
	    .def("__getitem__", [](hydra::Vector4R &obj,
				   hydra::GInt_t idx) { return obj.get(idx); },
		 py::is_operator(), "idx"_a, "Set value at a particular index.")
	    .def("__setitem__",
		 [](hydra::Vector4R &obj, hydra::GInt_t idx,
		    hydra::GReal_t value) { return obj.set(idx, value); },
		 py::is_operator(), "idx"_a, "value"_a, "Get value from a particular index.");
}
}
#endif /* PYVECTOR4R_H_ */
