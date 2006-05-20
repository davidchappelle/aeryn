
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

/** \file print.hpp
 *  \brief Default declaration of Print template. 
 */	

#ifndef AERYN_PRINT_HPP
#define AERYN_PRINT_HPP



namespace Aeryn
{
	namespace details
	{
		/**	\brief Default declaration of Print template. 
		 *
		 *	The Print template is used to make sure the correct error
		 *	message is given by the IS_EQUAL and IS_NOT_EQUAL macros depending
		 *	on whether the type on test is streamable or not.
		 *
		 *	@see FuncName
		 *	@see IsStreamable
		 */
		template< bool IsStreamable, FuncName Func >
		class Print;
	}
}

#endif // AERYN_PRINT_HPP
