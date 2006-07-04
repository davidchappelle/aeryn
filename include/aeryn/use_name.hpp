
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

/** \file use_name.hpp
 *  \brief Definition of USE_NAME test condition macro and implementation function declaration.
 */	

#ifndef AERYN_USE_FUNC_NAME_HPP
#define AERYN_USE_FUNC_NAME_HPP

#include <string>

/**	\brief USE_NAME macro.
 *
 *	The test fixture name passed to a test case is often the same as the test fixture function name 
 *	itself. Therefore Aeryn provides a macro which extracts the test fixture function name
 *	and passes it to the test case. 
 *
 *	The USE_NAME works in the same way for class based test fixtures removing <code>Incarnate&</code>
 *	and <code>FunctionPtr</code>. 
 */
#define USE_NAME( name ) ::Aeryn::FormatName( #name ), name

namespace Aeryn
{
	/**	\brief Format name.
	 *
	 *	Removes <code>Incarnate&</code> and <code>FunctionPtr</code> from function name.
	 *
	 *	\param name The name to format.
	 */
	std::string FormatName
		( const std::string& name );
}

#endif // AERYN_USE_FUNC_NAME_HPP
