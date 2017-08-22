
/*----------------------------------------------------------------------------
 *
 *   Copyright (C) 2017 Antonio Augusto Alves Junior
 *
 *
 *   This file is part of the Hydra.Python Analysis Framework.
 *
 *   Hydra.Python is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Hydra.Python is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Hydra.Python.  If not, see <http://www.gnu.org/licenses/>.
 *
 *---------------------------------------------------------------------------*/

/*
 * PyRandom.h
 *
 *  Created on: 30 de jul de 2017
 *      Author: augalves
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
#ifndef PYRANDOM_H_
#define PYRANDOM_H_

#include <functional>
#include <hydra/Random.h>
#include <hydra/FunctionWrapper.h>
#include <thrust/distance.h>
#include <pybind11/pybind11.h>
#include <add_object.h>
#include <typedefs.h>

namespace py = pybind11;

#define RANDOM_SAMPLE_BODY(N,BACKEND,...) "Sample", [](hydra::Random<>& cobj, BACKEND##_vector_float##N & vect,\
std::array<double,N>const& min,\
std::array<double,N>const& max,\
py::function& funct)\
{\
auto functor = [=](unsigned int n, double* data) {return funct( __VA_ARGS__ ).cast<double>();}; \
auto wfunctor = hydra::wrap_lambda( functor ); \
auto middle = cobj.Sample(vect.begin(), vect.end(), min, max, wfunctor ); \
typedef decltype(vect.begin()) iter_t;\
return py::make_iterator<pybind11::return_value_policy::reference_internal,	iter_t, iter_t, typename iter_t::value_type>(vect.begin(),middle);\
},\
"Sample a "#N"-dimensional distribution defined by function(...) in the hyper cube with limits min and max"

namespace hydra_python {

template<>
void add_object<hydra::Random<> >(pybind11::module& m) {

	py::class_<hydra::Random<>>(m, "Random")
	//ctors
	.def(py::init<>()).def(py::init<unsigned int>())
	//set seed
	.def("SetSeed",
			[](hydra::Random<>& cobj, size_t seed) {cobj.SetSeed(seed);},
			"Set seed of the underlying random number generator.")
	//get seed
	.def("GetSeed", [](hydra::Random<>& cobj) {cobj.GetSeed();},
			"Get seed of the underlying random number generator.")
	//-----------------------------------------------------
	//host functions
	//-----------------------------------------------------
	// uniform
	.def("Uniform",
			[](hydra::Random<>& cobj, double min, double max, host_vector_float& vect) {
				cobj.Uniform( min, max, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers uniformly distributed in the  range [min, max].")
	//gauss
	.def("Gauss",
			[](hydra::Random<>& cobj, double mean, double sigma, host_vector_float& vect) {
				cobj.Gauss( mean, sigma, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Gaussian with mean and sigma.")
	//exp
	.def("Exp", [](hydra::Random<>& cobj, double tau, host_vector_float& vect) {
		cobj.Exp( tau, vect.begin(), vect.end());
	}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Exponential with tau.")
	//breit-wigner
	.def("BreitWigner",
			[](hydra::Random<>& cobj, double mean, double width, host_vector_float& vect) {
				cobj.BreitWigner( mean, width, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a BreitWigner with mean and width.")
	//Sample 1D
	.def("Sample",
			[](hydra::Random<>& cobj, host_vector_float& vect,
					double min, double max, py::function& funct) {

				auto functor = [=](unsigned int n, double* data) {return funct(data[0]).cast<double>();};
				auto wfunctor = hydra::wrap_lambda( functor );
				auto middle = cobj.Sample(vect.begin(), vect.end(), min, max, wfunctor );

				typedef decltype(vect.begin()) iter_t;

				return py::make_iterator<pybind11::return_value_policy::reference_internal,iter_t, iter_t,
							typename iter_t::value_type>(vect.begin(),middle);

	},"Sample a 1-dimensional distribution defined by function(...) in the interval with limits min and max" )
	.def(RANDOM_SAMPLE_BODY(2,  host, data[0], data[1]))
	.def(RANDOM_SAMPLE_BODY(3,  host, data[0], data[1], data[2]))
	.def(RANDOM_SAMPLE_BODY(4,  host, data[0], data[1], data[2], data[3]))
	.def(RANDOM_SAMPLE_BODY(5,  host, data[0], data[1], data[2], data[3], data[4]))
	.def(RANDOM_SAMPLE_BODY(6,  host, data[0], data[1], data[2], data[3], data[4], data[5]))
	.def(RANDOM_SAMPLE_BODY(7,  host, data[0], data[1], data[2], data[3], data[4], data[5], data[6]))
	.def(RANDOM_SAMPLE_BODY(8,  host, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]))
	.def(RANDOM_SAMPLE_BODY(9,  host, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8] ))
	.def(RANDOM_SAMPLE_BODY(10, host, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8],data[9] ))
	//device functions
	//-----------------------------------------------------
	// uniform
	.def("Uniform",
			[](hydra::Random<>& cobj, double min, double max, device_vector_float& vect) {
				cobj.Uniform( min, max, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers uniformly distributed in the  range [min, max].")
	//gauss
	.def("Gauss",
			[](hydra::Random<>& cobj, double mean, double sigma, device_vector_float& vect) {
				cobj.Gauss( mean, sigma, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Gaussian with mean and sigma.")
	//exp
	.def("Exp",
			[](hydra::Random<>& cobj, double tau, device_vector_float& vect) {
				cobj.Exp( tau, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Exponential with tau.")
	//breit-wigner
			.def("BreitWigner",
					[](hydra::Random<>& cobj, double mean, double width, device_vector_float& vect) {
		cobj.BreitWigner( mean, width, vect.begin(), vect.end());
	}, py::call_guard<py::gil_scoped_release>(),
	"Fill the container with random numbers distributed according a BreitWigner with mean and width.")
	//Sample 1D
	.def("Sample",
			[](hydra::Random<>& cobj, device_vector_float& vect,
					double min, double max, py::function& funct) {

		auto functor = [=](unsigned int n, double* data) {return funct(data[0]).cast<double>();};
		auto wfunctor = hydra::wrap_lambda( functor );
		auto middle = cobj.Sample(vect.begin(), vect.end(), min, max, wfunctor );
		typedef decltype(vect.begin()) iter_t;
		return py::make_iterator<pybind11::return_value_policy::reference_internal,iter_t, iter_t,
			typename iter_t::value_type>(vect.begin(),middle);
		//(size_t) thrust::distance(vect.begin(), middle);

	},"Sample a 1-dimensional distribution defined by function(...) in the interval with limits min and max" )
	.def(RANDOM_SAMPLE_BODY(2,  device, data[0], data[1]))
	.def(RANDOM_SAMPLE_BODY(3,  device, data[0], data[1], data[2]))
	.def(RANDOM_SAMPLE_BODY(4,  device, data[0], data[1], data[2], data[3]))
	.def(RANDOM_SAMPLE_BODY(5,  device, data[0], data[1], data[2], data[3], data[4]))
	.def(RANDOM_SAMPLE_BODY(6,  device, data[0], data[1], data[2], data[3], data[4], data[5]))
	.def(RANDOM_SAMPLE_BODY(7,  device, data[0], data[1], data[2], data[3], data[4], data[5], data[6]))
	.def(RANDOM_SAMPLE_BODY(8,  device, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]))
	.def(RANDOM_SAMPLE_BODY(9,  device, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8] ))
	.def(RANDOM_SAMPLE_BODY(10, device, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8],data[9] ))
	;
}

}

#endif /* PYRANDOM_H_ */
