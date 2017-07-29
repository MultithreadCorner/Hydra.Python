
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
 * @todo Uncomment the assignment binding after the actual implementation of `assign` and `scalartripler3` in Hydra.
 *
 */




#include <pybind11/pybind11.h>
#include "hydra/Vector4R.h"
#include "hydra/Vector3R.h"
#include "hydra/Types.h"
#include "hydra/Events.h"
#include "hydra/detail/Config.h"
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <sstream>

namespace py = pybind11;


PYBIND11_MODULE(HydraPython, m) {
  py::class_< hydra::Vector3R >(m, "Vector3R")
    .def(py::init<>())
    .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t>())
    .def(py::init<hydra::Vector3R>())
    .def("__imul__", &hydra::Vector3R::operator*=)
    .def("__itruediv__", &hydra::Vector3R::operator/=)
    //    .def("assign", [](hydra::Vector3R& v, hydra::Vector3R& other) {v = other;} )
    .def("__iadd__", &hydra::Vector3R::operator+=)
    .def("__isub__", &hydra::Vector3R::operator-=)
    .def("set", (void (hydra::Vector3R::*)(hydra::GInt_t, hydra::GReal_t)) &hydra::Vector3R::set)
    .def("set", (void (hydra::Vector3R::*)(hydra::GReal_t, hydra::GReal_t, hydra::GReal_t)) &hydra::Vector3R::set)
    .def("applyRotateEuler", &hydra::Vector3R::applyRotateEuler)
    .def("get", &hydra::Vector3R::get)
    .def("dot", &hydra::Vector3R::dot)
    .def("d3mag", &hydra::Vector3R::d3mag)
    .def("__repr__", [](const hydra::Vector3R& e) { std::stringstream ss; ss << e; return ss.str(); })
    .def(hydra::GReal_t() * py::self)
    .def(py::self * hydra::GReal_t())
    .def(py::self * hydra::Vector3R())
    .def(py::self / hydra::GReal_t())
    .def(py::self + hydra::Vector3R())
    .def(py::self - hydra::Vector3R())
    .def("__eq__", [](const hydra::Vector3R& one, const hydra::Vector3R& two){
        for (auto i = 0; i < 3; ++i)
            if (one.get(i) != two.get(i))
                return false;
        return true;
    }, py::is_operator())
    .def("__ne__", [](const hydra::Vector3R& one, const hydra::Vector3R& two){
        for (auto i = 0; i < 3; ++i)
            if (one.get(i) != two.get(i))
                return true;
        return false;
    }, py::is_operator())
    .def("__getitem__", [](hydra::Vector3R& obj, hydra::GInt_t idx){
        return obj.get(idx);
    }, py::is_operator())
    .def("__setitem__", [](hydra::Vector3R& obj, hydra::GInt_t idx, hydra::GReal_t value){
        return obj.set(idx, value);
    }, py::is_operator())
  ;

  py::class_< hydra::Vector4R >(m, "Vector4R")
    .def(py::init<>())
    .def(py::init<hydra::GReal_t, hydra::GReal_t, hydra::GReal_t, hydra::GReal_t>())
    .def(py::init<hydra::Vector4R>())
    .def("__init__", [](hydra::Vector4R& vec, std::vector<hydra::GReal_t>& lst) {
	if (lst.size() == 4) {
	  vec = hydra::Vector4R();
	  for(int i = 0; i < 4; ++i)
	    vec.set(i, lst[i]);
	  return;
	}
	throw pybind11::type_error("list argument does not contain exactly 4 values!");
      })
    .def("set", (void (hydra::Vector4R::*)(hydra::GInt_t, hydra::GReal_t)) &hydra::Vector4R::set)
    .def("set", (void (hydra::Vector4R::*)(hydra::GReal_t, hydra::GReal_t, hydra::GReal_t, hydra::GReal_t)) &hydra::Vector4R::set)
    .def("__imul__", &hydra::Vector4R::operator*=)
    .def("__itruediv__", &hydra::Vector4R::operator/=)
    .def("assign", [](hydra::Vector4R& v, hydra::Vector4R& other) {v = other;} )    
    .def("__iadd__", &hydra::Vector4R::operator+=)
    .def("__isub__", &hydra::Vector4R::operator-=)
    .def("get", &hydra::Vector4R::get)
    .def("cont", &hydra::Vector4R::cont)
    .def("mass2", &hydra::Vector4R::mass2)
    .def("mass", &hydra::Vector4R::mass)
    .def("applyRotateEuler", &hydra::Vector4R::applyRotateEuler)
    .def("applyBoostTo", (void (hydra::Vector4R::*)(const hydra::Vector4R&, bool)) &hydra::Vector4R::applyBoostTo, py::arg("p4"), py::arg("inverse")=false)
    .def("applyBoostTo", (void (hydra::Vector4R::*)(const hydra::Vector3R&, bool)) &hydra::Vector4R::applyBoostTo, py::arg("boost"), py::arg("inverse")=false)
    .def("applyBoostTo", (void (hydra::Vector4R::*)(const hydra::GReal_t, const hydra::GReal_t, const hydra::GReal_t, bool inverse)) &hydra::Vector4R::applyBoostTo, py::arg("bx"), py::arg("by"), py::arg("bz"), py::arg("inverse")=false)
    .def("cross", &hydra::Vector4R::cross)
    .def("dot", &hydra::Vector4R::dot)
    .def("d3mag", &hydra::Vector4R::d3mag)
    //    .def("scalartripler3", &hydra::Vector4R::scalartripler3)
    .def("dotr3", &hydra::Vector4R::dotr3)
    .def("mag2r3", &hydra::Vector4R::mag2r3)
    .def("magr3", &hydra::Vector4R::magr3)
    .def("__repr__", [](const hydra::Vector4R& e) { std::stringstream ss; ss << e; return ss.str(); })
    .def(hydra::GReal_t() * py::self)
    .def(py::self * hydra::GReal_t())
    .def(py::self * hydra::Vector4R())
    .def(py::self / hydra::GReal_t())
    .def(py::self + hydra::Vector4R())
    .def(py::self - hydra::Vector4R())
    .def("__eq__", [](const hydra::Vector4R& one, const hydra::Vector4R& two){
        for (auto i = 0; i < 4; ++i)
            if (one.get(i) != two.get(i))
              return false;
        return true;
    }, py::is_operator())
    .def("__ne__", [](const hydra::Vector4R& one, const hydra::Vector4R& two){
        for (auto i = 0; i < 4; ++i)
            if (one.get(i) != two.get(i))
                return true;
        return false;
    }, py::is_operator())
    .def("__getitem__", [](hydra::Vector4R& obj, hydra::GInt_t idx){
        return obj.get(idx);
    }, py::is_operator())
    .def("__setitem__", [](hydra::Vector4R& obj, hydra::GInt_t idx, hydra::GReal_t value){
        return obj.set(idx, value);
    }, py::is_operator())
    ;
}
