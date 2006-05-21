
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

/** \file func_name.hpp
 *  \brief Definition of FuncName enum.
 */	

#ifndef AERYN_FUNC_NAME_HPP
#define AERYN_FUNC_NAME_HPP


namespace Aeryn
{
	namespace details
	{
		/**	\enum FuncName
		 *	\brief Used to select the correct Print specialisation.
		 *
		 *	@see Print
		 */
		enum FuncName
		{
			IsEqualFunc,
			IsNotEqualFunc
		};
	}
}

#endif // AERYN_FUNC_NAME_HPP
