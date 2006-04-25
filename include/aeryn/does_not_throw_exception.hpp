
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

/** \file does_not_throw_exception.hpp
 *  \brief Definition of does_not_throw_exception test condition macro.
 */	

#ifndef DOES_NOT_THROW_EXCEPTION_HPP
#define DOES_NOT_THROW_EXCEPTION_HPP

#include <aeryn/test_failure.hpp>
#include <string>

/**	\brief DOES_NOT_THROW_EXCEPTION test condition macro.
 *
 *	<b>Failure condition:</b> The DOES_NOT_THROW_EXCEPTION test condition throws if the statement 
 *	contained in the statement parameter throws an exception of any type. Eg:
 *
 *	DOES_NOT_THROW_EXCEPTION( Thrower() );
 *
 *	Where Thrower is a class that throws from its constructor.
 *
 *	<b>Failure message:</b>	Exception Thrown
 *
 *	<b>Example:</b>	IS_NOT_EQUAL( NonThrower() );
 *
 *	Where NonThrower is a class that does not throw from its constructor.
 */
#define DOES_NOT_THROW_EXCEPTION( statement ) \
	try \
	{ \
		statement; \
	} \
	catch( ... ) \
	{ \
		throw ::Aeryn::TestFailure( std::string("Exception Thrown"), __LINE__, __FILE__ ); \
	} 

#endif // AERYN_THROWS_EXCEPTION_HPP
