
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

PYBIND11_MAKE_OPAQUE(hydra::mc_host_vector<double>);

PYBIND11_MODULE(HydraPython, m) {

    py::class_<hydra::mc_host_vector<double>>(m, "host_vector_float")
        .def(py::init<>())
		.def(py::init<size_t>())
		.def(py::init<size_t, double>())
		.def("resize",	 &hydra::hydra::mc_host_vector<double>::resize)
		.def("size", 	 &hydra::hydra::mc_host_vector<double>::size)
		.def("max_size", &hydra::hydra::mc_host_vector<double>::max_size)
		.def("reserve",  &hydra::hydra::mc_host_vector<double>::reserve)
		.def("capacity", &hydra::hydra::mc_host_vector<double>::capacity)
		.def("shrink_to_fit", &hydra::hydra::mc_host_vector<double>::shrink_to_fit)
		.def("front", &hydra::hydra::mc_host_vector<double>::front )
		.def("back",  &hydra::hydra::mc_host_vector<double>::back)
		.def("data",  &hydra::hydra::mc_host_vector<double>::data)
		.def("clear", &hydra::hydra::mc_host_vector<double>::clear)
		.def("empty", &hydra::hydra::mc_host_vector<double>::empty)
		.def("push_back", &hydra::hydra::mc_host_vector<double>::push_back)
		.def("pop_back", &hydra::hydra::mc_host_vector<double>::)
		//.def("swap", &hydra::hydra::mc_host_vector<double>::swap)
		.def("erase", &hydra::hydra::mc_host_vector<double>::erase)
		.def("insert", &hydra::hydra::mc_host_vector<double>::insert)
		.def("assign", &hydra::hydra::mc_host_vector<double>::assign )
		.def("assign", &hydra::hydra::mc_host_vector<double>::assign)


								;
}


