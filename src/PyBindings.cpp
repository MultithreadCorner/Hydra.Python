
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
 * PyBindings.cpp
 *
 *  Created on: July 30, 2017
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

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//Hydra.Python helpers
#include <add_object.h>
#include <bind_container.h>
#include <casters.h>
#include <typedefs.h>
#include <make_opaque.h>
// Hydra.Python binded Hydra classes
#include <PyRandom.h>
#include <PyEvents.h>
#include <PyVector3R.h>
#include <PyVector4R.h>
#include <PyPhaseSpace.h>


namespace py = pybind11;
namespace hypy = hydra_python;



PYBIND11_MODULE(HydraPython, m) {

hypy::add_object< hydra::Vector3R >(m);
hypy::add_object< hydra::Vector4R >(m);
hypy::add_object< hydra::Random<thrust::random::default_random_engine> >(m);
hypy::add_object< hydra::Events<4, hydra::host::sys_t> >(m);
hypy::add_object< hydra::PhaseSpace<4, thrust::random::default_random_engine> >(m);

//decay container host
hypy::bind_vector< hypy::host_decays_2>(m, "host_decays_2");
hypy::bind_vector< hypy::host_decays_3>(m, "host_decays_3");
hypy::bind_vector< hypy::host_decays_4>(m, "host_decays_4");
hypy::bind_vector< hypy::host_decays_5>(m, "host_decays_5");
hypy::bind_vector< hypy::host_decays_6>(m, "host_decays_6");
hypy::bind_vector< hypy::host_decays_7>(m, "host_decays_7");
hypy::bind_vector< hypy::host_decays_8>(m, "host_decays_8");
hypy::bind_vector< hypy::host_decays_9>(m, "host_decays_9");
hypy::bind_vector< hypy::host_decays_10>(m,"host_decays_10");

//decay container device
hypy::bind_vector< hypy::device_decays_2>(m, "device_decays_2");
hypy::bind_vector< hypy::device_decays_3>(m, "device_decays_3");
hypy::bind_vector< hypy::device_decays_4>(m, "device_decays_4");
hypy::bind_vector< hypy::device_decays_5>(m, "device_decays_5");
hypy::bind_vector< hypy::device_decays_6>(m, "device_decays_6");
hypy::bind_vector< hypy::device_decays_7>(m, "device_decays_7");
hypy::bind_vector< hypy::device_decays_8>(m, "device_decays_8");
hypy::bind_vector< hypy::device_decays_9>(m, "device_decays_9");
hypy::bind_vector< hypy::device_decays_10>(m,"device_decays_10");

//host vectors
hypy::bind_vector< hypy::host_vector_float  >(m,"host_vector_float");
hypy::bind_vector< hypy::host_vector_float2 >(m,"host_vector_float2");
hypy::bind_vector< hypy::host_vector_float3 >(m,"host_vector_float3");
hypy::bind_vector< hypy::host_vector_float4 >(m,"host_vector_float4");
hypy::bind_vector< hypy::host_vector_float5 >(m,"host_vector_float5");
hypy::bind_vector< hypy::host_vector_float6 >(m,"host_vector_float6");
hypy::bind_vector< hypy::host_vector_float7 >(m,"host_vector_float7");
hypy::bind_vector< hypy::host_vector_float8 >(m,"host_vector_float8");
hypy::bind_vector< hypy::host_vector_float9 >(m,"host_vector_float9");
hypy::bind_vector< hypy::host_vector_float10>(m,"host_vector_float10");

//device vector
hypy::bind_vector< hypy::device_vector_float  >(m,"device_vector_float");
hypy::bind_vector< hypy::device_vector_float2 >(m,"device_vector_float2");
hypy::bind_vector< hypy::device_vector_float3 >(m,"device_vector_float3");
hypy::bind_vector< hypy::device_vector_float4 >(m,"device_vector_float4");
hypy::bind_vector< hypy::device_vector_float5 >(m,"device_vector_float5");
hypy::bind_vector< hypy::device_vector_float6 >(m,"device_vector_float6");
hypy::bind_vector< hypy::device_vector_float7 >(m,"device_vector_float7");
hypy::bind_vector< hypy::device_vector_float8 >(m,"device_vector_float8");
hypy::bind_vector< hypy::device_vector_float9 >(m,"device_vector_float9");
hypy::bind_vector< hypy::device_vector_float10>(m,"device_vector_float10");


}
