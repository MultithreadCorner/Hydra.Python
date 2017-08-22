
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
 * add_object.h
 *
 *  Created on: 30 de jul de 2017
 *      Author: augalves
 */

/*
 * @file
 * 
 * @ingroup
 * 
 * @brief This file declare the add_object function
 *
 * @todo 
 *
 */
#ifndef ADD_OBJECT_H_
#define ADD_OBJECT_H_

#include <pybind11/pybind11.h>

namespace hydra_python {

template<typename T>
void add_object(pybind11::module& m);

}

#endif /* ADD_OBJECT_H_ */
