
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2005 Paul Grenyer
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/** \file preprocessor.hpp
 *  \brief Helper marcos
 */	

#ifndef AERYN_PREPROCESSOR_HPP
#define AERYN_PREPROCESSOR_HPP

/** \brief Make a reasaonbly "unique" identifier name by joining the "basename" with
 *	the current file line number.
 */
#define AERYN_UNIQUE_NAME(basename) AERYN_UNIQUE_NAME_2(basename, __LINE__)

/**	\brief Helper for AERYN_UNIQUE_NAME
 *
 * @see AERYN_UNIQUE_NAME
 * @internal
 */
#define AERYN_UNIQUE_NAME_2(first, second) AERYN_UNIQUE_NAME_3(first, second)

/**	\brief Helper for AERYN_UNIQUE_NAME
 *	@see AERYN_UNIQUE_NAME
 *	@internal
 */
#define AERYN_UNIQUE_NAME_3(first, second) first##second

#endif

