
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
 * make_opaque.h
 *
 *  Created on: 3 de ago de 2017
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
#ifndef MAKE_OPAQUE_H_
#define MAKE_OPAQUE_H_

//hydra.python
#include <typedefs.h>
//pybind11
#include <pybind11/pybind11.h>

namespace hypy = hydra_python;


PYBIND11_MAKE_OPAQUE(hypy::host_vector_float );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float2 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float3 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float4 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float5 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float6 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float7 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float8 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float9 );
PYBIND11_MAKE_OPAQUE(hypy::host_vector_float10 );
PYBIND11_MAKE_OPAQUE(hypy::host_decays_2);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_3);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_4);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_5);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_6);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_7);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_8);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_9);
PYBIND11_MAKE_OPAQUE(hypy::host_decays_10);

PYBIND11_MAKE_OPAQUE(hypy::device_vector_float );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float2 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float3 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float4 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float5 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float6 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float7 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float8 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float9 );
PYBIND11_MAKE_OPAQUE(hypy::device_vector_float10 );

PYBIND11_MAKE_OPAQUE(hypy::device_decays_2);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_3);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_4);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_5);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_6);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_7);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_8);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_9);
PYBIND11_MAKE_OPAQUE(hypy::device_decays_10);

#endif /* MAKE_OPAQUE_H_ */
