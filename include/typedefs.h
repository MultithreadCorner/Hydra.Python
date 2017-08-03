
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
 * typedefs.h
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
#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <hydra/Containers.h>
#include <hydra/multiarray.h>
#include <hydra/device/System.h>
#include <hydra/host/System.h>


namespace hydra_python {


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


}  // namespace hydra_python


#endif /* TYPEDEFS_H_ */
