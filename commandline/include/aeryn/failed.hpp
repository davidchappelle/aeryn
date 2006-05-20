
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

/** \file failed.hpp
 *  \brief Definition of FAILED test condition macro and implementation function declaration.
 */	

#ifndef AERYN_FAILED_HPP
#define AERYN_FAILED_HPP

#ifdef FAILED
#undef FAILED
#endif

/**	\brief FAILED test condition macro.
 *
 *	<b>Failure condition:</b>	The FAILED test condition always throws. It is intended to be used 
 *	to indicate when code that should not be executed under normal conditions has been reached.
 *
 *	<b>Failure message:</b>	The string literal contained within msg. 
 *
 *	<b>Example:</b><code> try
 *	{
 *		…
 *	}
 *	catch( const std::exception& e )
 *	{
 *		FAILED( e.what() );
 *	}</code>
 *
 */
#define FAILED( msg ) ::Aeryn::Failed( msg, __LINE__, __FILE__ )

namespace Aeryn
{
	/**	\brief Reports a failed test by throwing a TestFailure exception.
	 *
	 *	\param msg A message to indicate the failure.
	 *	\param line The line the failure occurred on.
	 *	\param file The file the failure occurred in.
	 *	\throws TestFailure Always throws.
	 */
	void Failed
		( const char* msg, unsigned long line, const char* file );
}

#endif // AERYN_FAILED_HPP
