
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


#include <hydra/Random.h>
#include <pybind11/pybind11.h>
#include <add_object.h>

namespace py = pybind11;

namespace hydra_python {

template<>
void add_object<hydra::Random<> >(pybind11::module& m) {

	py::class_<hydra::Random<>>(m, "Random")
	//ctors
	.def(py::init<>())
	.def(py::init<unsigned int>())
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
			[](hydra::Random<>& cobj, double min, double max, hydra::mc_host_vector<double>& vect) {
				cobj.Uniform( min, max, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers uniformly distributed in the  range [min, max].")
	//gauss
	.def("Gauss",
			[](hydra::Random<>& cobj, double mean, double sigma, hydra::mc_host_vector<double>& vect) {
				cobj.Gauss( mean, sigma, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Gaussian with mean and sigma.")
	//exp
	.def("Exp",
			[](hydra::Random<>& cobj, double tau, hydra::mc_host_vector<double>& vect) {
				cobj.Exp( tau, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Exponential with tau.")
	//breit-wigner
	.def("BreitWigner",
			[](hydra::Random<>& cobj, double mean, double width, hydra::mc_host_vector<double>& vect) {
				cobj.BreitWigner( mean, width, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a BreitWigner with mean and width.")

    //-----------------------------------------------------
	//device functions
	//-----------------------------------------------------
	// uniform
	.def("Uniform",
			[](hydra::Random<>& cobj, double min, double max, hydra::mc_device_vector<double>& vect) {
				cobj.Uniform( min, max, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers uniformly distributed in the  range [min, max].")
	//gauss
	.def("Gauss",
			[](hydra::Random<>& cobj, double mean, double sigma, hydra::mc_device_vector<double>& vect) {
				cobj.Gauss( mean, sigma, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Gaussian with mean and sigma.")
	//exp
	.def("Exp",
			[](hydra::Random<>& cobj, double tau, hydra::mc_device_vector<double>& vect) {
				cobj.Exp( tau, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a Exponential with tau.")
	//breit-wigner
	.def("BreitWigner",
			[](hydra::Random<>& cobj, double mean, double width, hydra::mc_device_vector<double>& vect) {
				cobj.BreitWigner( mean, width, vect.begin(), vect.end());
			}, py::call_guard<py::gil_scoped_release>(),
			"Fill the container with random numbers distributed according a BreitWigner with mean and width.");
}

}



#endif /* PYRANDOM_H_ */
