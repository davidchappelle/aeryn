
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

/** \file is_true.hpp
 *	\brief Definition of IS_TRUE test condition macro and implementation function declaration.
 */	

#ifndef AERYN_IS_TRUE_HPP
#define AERYN_IS_TRUE_HPP

/**	\brief IS_TRUE test condition macro.
 *
 *	<b>Failure condition:</b> The IS_TRUE test condition throws if the result of executing <code>code</code>
 *	evaluates to false. Eg:
 *
 *	IS_TRUE( false );
 *
 *	<b>Failure message:</b> A string containing the complete test condition. Eg:
 *
 *	IS_TRUE( false )
 *
 *	<b>Example:</b> <code>IS_TRUE( lifeTheUniverseAndEverything == 42 );</code>
 */
#define IS_TRUE( code ) ::Aeryn::IsTrue( code, #code, __LINE__, __FILE__ )

namespace Aeryn
{
	/**	\brief Determines if an expression evaluates to true. Throws if it does not.
	 *
	 *	\param result The result of the expression.
	 *	\param code A textural representation of the expression.
	 *	\param line The line from which IsTrue is being called.
	 *	\param file The file from which IsTrue is being called.
	 *	\throws TestFailure If the expression evaluates to false.
	 */
	void IsTrue
		(	bool result, 
			const char* code, 
			unsigned long line, 
			const char* file );	
}

#endif // AERYN_IS_TRUE_HPP
