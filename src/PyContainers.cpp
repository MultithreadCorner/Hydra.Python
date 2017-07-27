
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
 * PyContainers.cpp
 *
 *  Created on: Jul 27, 2017
 *      Author: Antonio Augusto Alves Junior
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


#include <hydra/Containers.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(HydraPython, m) {

    py::class_<hydra::mc_host_vector<double>>(m, "Random")
        .def(py::init<unsigned int>())
		.def("SetSeed", &hydra::Random<>::SetSeed)
        .def("GetSeed", &hydra::Random<>::GetSeed)
		;
}


