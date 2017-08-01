
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
 * PyBindings.cpp
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


//hydra
#include <hydra/Containers.h>
#include <hydra/multiarray.h>
#include <hydra/device/System.h>
#include <hydra/host/System.h>

//pybind11
#include <pybind11/pybind11.h>

//Hydra.Python
#include <add_object.h>
#include <bind_container.h>
#include <casters.h>
//Hydra.Python hydra classes
#include <PyRandom.h>

namespace py = pybind11;
namespace hypy = hydra_python;

typedef hydra::mc_host_vector<double>                      host_vector_float;
typedef hydra::multiarray<2,  double, hydra::host::sys_t>  host_vector_float2;
typedef hydra::multiarray<3,  double, hydra::host::sys_t>  host_vector_float3;
typedef hydra::multiarray<4,  double, hydra::host::sys_t>  host_vector_float4;
typedef hydra::multiarray<5,  double, hydra::host::sys_t>  host_vector_float5;
typedef hydra::multiarray<6,  double, hydra::host::sys_t>  host_vector_float6;
typedef hydra::multiarray<7,  double, hydra::host::sys_t>  host_vector_float7;
typedef hydra::multiarray<8,  double, hydra::host::sys_t>  host_vector_float8;
typedef hydra::multiarray<9,  double, hydra::host::sys_t>  host_vector_float9;
typedef hydra::multiarray<10, double, hydra::host::sys_t>  host_vector_float10;

typedef hydra::mc_device_vector<double>                      device_vector_float;
typedef hydra::multiarray<2,  double, hydra::device::sys_t>  device_vector_float2;
typedef hydra::multiarray<3,  double, hydra::device::sys_t>  device_vector_float3;
typedef hydra::multiarray<4,  double, hydra::device::sys_t>  device_vector_float4;
typedef hydra::multiarray<5,  double, hydra::device::sys_t>  device_vector_float5;
typedef hydra::multiarray<6,  double, hydra::device::sys_t>  device_vector_float6;
typedef hydra::multiarray<7,  double, hydra::device::sys_t>  device_vector_float7;
typedef hydra::multiarray<8,  double, hydra::device::sys_t>  device_vector_float8;
typedef hydra::multiarray<9,  double, hydra::device::sys_t>  device_vector_float9;
typedef hydra::multiarray<10, double, hydra::device::sys_t>  device_vector_float10;


PYBIND11_MAKE_OPAQUE(host_vector_float );
PYBIND11_MAKE_OPAQUE(host_vector_float2 );
PYBIND11_MAKE_OPAQUE(host_vector_float3 );
PYBIND11_MAKE_OPAQUE(host_vector_float4 );
PYBIND11_MAKE_OPAQUE(host_vector_float5 );
PYBIND11_MAKE_OPAQUE(host_vector_float6 );
PYBIND11_MAKE_OPAQUE(host_vector_float7 );
PYBIND11_MAKE_OPAQUE(host_vector_float8 );
PYBIND11_MAKE_OPAQUE(host_vector_float9 );
PYBIND11_MAKE_OPAQUE(host_vector_float10 );

PYBIND11_MAKE_OPAQUE(device_vector_float );
PYBIND11_MAKE_OPAQUE(device_vector_float2 );
PYBIND11_MAKE_OPAQUE(device_vector_float3 );
PYBIND11_MAKE_OPAQUE(device_vector_float4 );
PYBIND11_MAKE_OPAQUE(device_vector_float5 );
PYBIND11_MAKE_OPAQUE(device_vector_float6 );
PYBIND11_MAKE_OPAQUE(device_vector_float7 );
PYBIND11_MAKE_OPAQUE(device_vector_float8 );
PYBIND11_MAKE_OPAQUE(device_vector_float9 );
PYBIND11_MAKE_OPAQUE(device_vector_float10 );




PYBIND11_MODULE(HydraPython, m) {

hypy::add_object< hydra::Random<> >(m);

hypy::bind_vector< host_vector_float  >(m,"host_vector_float");
hypy::bind_vector< host_vector_float2 >(m,"host_vector_float2");
hypy::bind_vector< host_vector_float3 >(m,"host_vector_float3");
hypy::bind_vector< host_vector_float4 >(m,"host_vector_float4");
hypy::bind_vector< host_vector_float5 >(m,"host_vector_float5");
hypy::bind_vector< host_vector_float6 >(m,"host_vector_float6");
hypy::bind_vector< host_vector_float7 >(m,"host_vector_float7");
hypy::bind_vector< host_vector_float8 >(m,"host_vector_float8");
hypy::bind_vector< host_vector_float9 >(m,"host_vector_float9");
hypy::bind_vector< host_vector_float10>(m,"host_vector_float10");


hypy::bind_vector< device_vector_float  >(m,"device_vector_float");
hypy::bind_vector< device_vector_float2 >(m,"device_vector_float2");
hypy::bind_vector< device_vector_float3 >(m,"device_vector_float3");
hypy::bind_vector< device_vector_float4 >(m,"device_vector_float4");
hypy::bind_vector< device_vector_float5 >(m,"device_vector_float5");
hypy::bind_vector< device_vector_float6 >(m,"device_vector_float6");
hypy::bind_vector< device_vector_float7 >(m,"device_vector_float7");
hypy::bind_vector< device_vector_float8 >(m,"device_vector_float8");
hypy::bind_vector< device_vector_float9 >(m,"device_vector_float9");
hypy::bind_vector< device_vector_float10>(m,"device_vector_float10");


}


