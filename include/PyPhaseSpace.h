
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
#ifndef PYPHASESPACE_H_
#define PYPHASESPACE_H_
#include <hydra/device/System.h>
#include <hydra/host/System.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <vector>
#include "hydra/PhaseSpace.h"
#include "hydra/Types.h"
#include "hydra/Vector4R.h"

namespace py = pybind11;

namespace hydra_python {

#define PHASESPACE_GENERATE_BODY(N, RNG, BACKEND)                  \
	"Generate" #BACKEND,                                       \
	    [](hydra::PhaseSpace<N, RNG>& p, hydra::Vector4R& vec, \
	       hydra::Events<N, hydra::BACKEND::sys_t>& e) {       \
		    p.Generate(vec, e.begin(), e.end());           \
	    }

#define PHASESPACE_GENERATE_BODY_2(N, RNG, BACKEND)                            \
	"Generate" #BACKEND, [](hydra::PhaseSpace<N, RNG>& p,                  \
				hydra::Events<N, hydra::BACKEND::sys_t>& e1,   \
				hydra::Events<N, hydra::BACKEND::sys_t>& e2) { \
		p.Generate(e1.DaughtersBegin(0), e1.DaughtersEnd(0),           \
			   e2.begin());                                        \
	}

#define ADD_FUNCTOR(...)                                  \
	auto functor = [=](hydra::Vector4R* data) {       \
		return funct(__VA_ARGS__).cast<double>(); \
	};                                                \
	auto wfunctor = hydra::wrap_lambda(functor);

#define ADD1 data[0]
#define ADD2 data[0], data[1]
#define ADD3 data[0], data[1], data[2]
#define ADD4 data[0], data[1], data[2], data[3]
#define ADD5 data[0], data[1], data[2], data[3], data[4]
#define ADD6 data[0], data[1], data[2], data[3], data[4], data[5]
#define ADD7 data[0], data[1], data[2], data[3], data[4], data[5], data[6]
#define ADD8 data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]
#define ADD9 data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]
#define ADD10 data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9]

#define PHASESPACE_AVERAGEON_BODY(N, RNG, BACKEND)                       \
	"AverageON" #BACKEND,                                            \
	    [](hydra::PhaseSpace<N, RNG>& p, hydra::Vector4R& v,         \
	       py::function& funct, size_t nentries) {                   \
		    ADD_FUNCTOR(ADD##N)               \
		    return p.AverageOn(hydra::BACKEND::sys, v, wfunctor, \
				       nentries);                        \
	    }

#define PHASESPACE_AVERAGEON_BODY_2(N, RNG, BACKEND)                         \
	"AverageON" #BACKEND, [](hydra::PhaseSpace<N, RNG>& p,               \
				 hydra::Events<N, hydra::BACKEND::sys_t>& e, \
				 py::function& fun) { return 42.0; }

/*

 #define PHASESPACE_GENERATE_BODY_2(N, RNG, BACKEND) "Generate"#BACKEND,
[](hydra::PhaseSpace<N, RNG>& p, hydra::Events<N, hydra::BACKEND::sys_t>& e1,
hydra::Events<N, hydra::BACKEND::sys_t>& e2) {\
    p.Generate(e1.DaughtersBegin(0), e1.DaughtersEnd(0), e2.begin());\
}
*/

#define PHASESPACE_CLASS_BODY(N, RNG, BACKEND)                      \
	py::class_<hydra::PhaseSpace<N, RNG> >(m, "PhaseSpace" #N) \
	    .def(py::init<hydra::GReal_t,                           \
			  const std::array<hydra::GReal_t, N>&>())  \
	    .def("GetSeed", &hydra::PhaseSpace<N, RNG>::GetSeed)    \
	    .def("SetSeed", &hydra::PhaseSpace<N, RNG>::SetSeed)    \
	    .def(PHASESPACE_GENERATE_BODY(N, RNG, host))            \
	    .def(PHASESPACE_GENERATE_BODY(N, RNG, device))          \
	    .def(PHASESPACE_AVERAGEON_BODY(N, RNG, host))           \
	    .def(PHASESPACE_AVERAGEON_BODY(N, RNG, device))         \
	    .def(PHASESPACE_AVERAGEON_BODY_2(N, RNG, host))         \
	    .def(PHASESPACE_AVERAGEON_BODY_2(N, RNG, device));
/*
	    .def(PHASESPACE_GENERATE_BODY_2(N, RNG, host))          \
	    .def(PHASESPACE_GENERATE_BODY_2(N, RNG, device));
*/

template <>
void add_object<hydra::PhaseSpace<4, thrust::random::default_random_engine> >(
    pybind11::module& m) {
	PHASESPACE_CLASS_BODY(1, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(2, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(3, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(4, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(5, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(6, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(7, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(8, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(9, thrust::random::default_random_engine, host);
	PHASESPACE_CLASS_BODY(10, thrust::random::default_random_engine, host);
}
}
#endif /* PYPHASESPACE_H_ */
