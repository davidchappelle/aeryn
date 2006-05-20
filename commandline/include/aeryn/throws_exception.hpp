
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

/** \file throws_exception.hpp
 *  \brief THROWS_EXCEPTION definition.
 */	

#ifndef AERYN_THROWS_EXCEPTION_HPP
#define AERYN_THROWS_EXCEPTION_HPP

#include <aeryn/test_failure.hpp>
#include <string>

/**	\brief THROWS_EXCEPTION test condition macro.
 *
 *	<b>Failure condition:</b> The THROWS_EXCEPTION test condition throws if the 
 *	statement contained in the <code>statement</code> parameter does not throw 
 *	an exception of the type exception_type. Eg:
 *
 *	THROWS_EXCEPTION( NonThrower(), std::exception );
 *
 *	Where <code>NonThrower</code> is a class that does not throw from its constructor.
 *
 *	<b>Failure message:</b>	A simple message saying that the code failed to throw an 
 *	exception of the right type. E.g:
 *
 *	Failed to throw <code>std::exception</code>
 *
 *	<b>Example:</b> <code>IS_NOT_EQUAL( Thrower(), std::exception );</code>
 *
 *	Where <code>Thrower</code> is a class that throws from its constructor.
 */
#define THROWS_EXCEPTION( statement, exception_type ) \
	try \
	{ \
		statement; \
		throw ::Aeryn::TestFailure( std::string("Failed to throw ") + #exception_type, __LINE__, __FILE__ ); \
	} \
	catch( const ::Aeryn::TestFailure& ) \
	{ \
		throw; \
	} \
	catch( const exception_type& ) \
	{ \
	} \
	catch( ... ) \
	{ \
		throw ::Aeryn::TestFailure( std::string("Threw wrong exception: not ") + #exception_type, __LINE__, __FILE__ ); \
	}

#endif // AERYN_THROWS_EXCEPTION_HPP
