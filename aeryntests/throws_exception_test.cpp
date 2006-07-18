
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

/** \file throws_exception_test.cpp
*  \brief Definition of THROWS_EXCEPTION and DOES_NOT_THROW_EXCEPTION tests.
 */	

#include "throws_exception_test.hpp"
#include <aeryn/test_funcs.hpp>
#include <stdexcept>

namespace Aeryn
{
	namespace
	{
		/**	\brief Dummy class that throws on construction. */
		template< typename T >
		class Thrower
		{
		public:
			/**	\brief Throws an exception of type T. */
			Thrower()
			{
				throw T();
			}
		};

		/**	\brief Dummy class that does not throw. */
		class NonThrower
		{
		};

		/**	\brief Example file name. */
		const char* const filename = __FILE__;
	}		
	
	//////////////////////////////////////////////////////////////////////////
	void ThrowsExceptionTest
		()
	{
		THROWS_EXCEPTION( Thrower< std::exception >(), std::exception );
	}

	//////////////////////////////////////////////////////////////////////////
	void ThrowsExceptionFailTest
		()
	{
		unsigned long line = 0;

		try
		{
			line = __LINE__; THROWS_EXCEPTION( NonThrower(), std::exception );
			FAILED( "THROWS_EXCEPTION( \"\";, std::exception ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "Failed to throw std::exception", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void ThrowsExceptionWrongExceptionTest
		()
	{
		unsigned long line = 0;

		try
		{
			line = __LINE__; THROWS_EXCEPTION( Thrower< std::exception >(), std::bad_alloc );
			FAILED( "THROWS_EXCEPTION( Thrower< std::exception >(), std::bad_alloc ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "Threw wrong exception: not std::bad_alloc", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void DoesNotThrowExceptionTest
		()
	{
		DOES_NOT_THROW_EXCEPTION( NonThrower() );
	}

	//////////////////////////////////////////////////////////////////////////
	void DoesNotThrowExceptionFailTest
		()
	{
		unsigned long line = 0;

		try
		{
			line = __LINE__; DOES_NOT_THROW_EXCEPTION( Thrower< std::exception >() );
			FAILED( "DOES_NOT_THROW_EXCEPTION( throw std::bad_alloc(); ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "Exception Thrown", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////	
}
