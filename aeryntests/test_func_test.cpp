
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

/** \file test_func_test.cpp
*  \brief Definition of test function tests.
 */	

#include "test_func_test.hpp"
#include <aeryn/test_funcs.hpp>
#include <limits>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		/**	\brief Example file name.*/
		const char* const filename = __FILE__;

		/**	\brief Dummy class to use in tests. */
		class A{};

		/**	\brief Dummy class to use in tests. */
		class B{};

		/**	\brief Dummy class to use in tests. */
		class C{};

		/**	\brief Dummy equality operator. 
		 *
		 *	\return false.
		 */
		bool operator==( const A&, const B& )
		{
			return false;
		}

		/**	\brief Dummy non-equality operator. 
		 *
		 *	\return false.
		 */
		bool operator!=( const B&, const C& )
		{
			return false;
		}

		/**	\brief Output operator for A.
		 *
		 *	\param os An output streem.
		 *	\return os.
		 */
		std::ostream& operator<<( std::ostream& os, const A& )
		{
			return os;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	void IsTrueTest
		()
	{
		try
		{
			IS_TRUE( true );						
		}
		catch( const TestFailure& )
		{
			FAILED( "IS_TRUE( true ) failed." );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsTrueFailTest
		()
	{
		unsigned long line = 0;
		
		try
		{
			line = __LINE__; IS_TRUE( false ); 
			FAILED( "IS_TRUE( false ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "IS_TRUE(false)", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsFalseTest
		()
	{
		try
		{
			IS_FALSE( false );
		}
		catch( const TestFailure& )
		{
			FAILED( "IS_FALSE( false ) failed." );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsFalseFailTest
		()
	{
		unsigned long line = 0;

		try
		{
			line = __LINE__; IS_FALSE( true ); 
			FAILED( "IS_FALSE( true ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "IS_FALSE(true)", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsEqualTest
		()
	{
		try
		{
			IS_EQUAL( 3, 3 );			
		}
		catch( const TestFailure& )
		{
			FAILED( "IS_EQUAL( true ) failed." );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsEqualFailTest
		()
	{
		unsigned long line = 0;
		
		try 
		{
			line = __LINE__; IS_EQUAL( "Hello, World!", "Hello, World" );
			FAILED( "IS_EQUAL( false ) failed" );
		}
		catch( const TestFailure& e )
		{
#ifdef NO_OUTPUT_OPERATOR_DETECTION
			const std::string expectedResult = "IS_EQUAL(\"Hello, World!\",\"Hello, World\")";
			IS_EQUAL( expectedResult, e.Failure() );
			
#else
			IS_EQUAL( "'Hello, World!' does not equal 'Hello, World'", e.Failure() );
#endif
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsEqualDoubleTest
		()
	{
		try
		{
			const double eps	= std::numeric_limits< double >::epsilon();
			const double a		= 1.0;
			const double b		= 1 + ( eps / 2 );
			IS_EQUAL( a, b );			
		}
		catch( const TestFailure& )
		{
			FAILED( "IS_EQUAL( double ) failed." );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsNotEqualTest
		()
	{
		try
		{
			IS_NOT_EQUAL( 3, 1 );
		}
		catch( const TestFailure& )
		{
			FAILED( "IS_NOT_EQUAL( false ) failed." );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsNotEqualFailTest
		()
	{
		unsigned long line = 0;

		try 
		{
			line = __LINE__; IS_NOT_EQUAL( "Hello, World!", "Hello, World!" );
			FAILED( "IS_NOT_EQUAL( true ) failed" );
		}
		catch( const TestFailure& e )
		{
#ifdef NO_OUTPUT_OPERATOR_DETECTION
			const std::string expectedResult = "IS_NOT_EQUAL(\"Hello, World!\",\"Hello, World!\")";
			IS_EQUAL( expectedResult, e.Failure() );
#else
			IS_EQUAL( "Expected not to get 'Hello, World!'", e.Failure() );
#endif
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsEqualMissingOutputOperator
		()
	{
		unsigned long line = 0;
		
		try
		{
			A a;
			B b;
			line = __LINE__; IS_EQUAL( a, b );
			FAILED( "IS_EQUAL( a,b ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "IS_EQUAL(a,b)", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsNotEqualMissingOutputOperator
		()
	{
		unsigned long line = 0;
		
		try
		{
			B b;
			C c;
			line = __LINE__; IS_NOT_EQUAL( b, c );
			FAILED( "IS_NOT_EQUAL( b,c ) failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "IS_NOT_EQUAL(b,c)", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void FailureTest
		()
	{
		unsigned long line = 0;
		
		try
		{
			line = __LINE__; FAILED( "Failed!" );
			FAILED( "Failed failed" );
		}
		catch( const TestFailure& e )
		{
			IS_EQUAL( "Failed!", e.Failure() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void MissingTestTest
		()
	{
		unsigned long line = 0;
		
		try
		{
			line = __LINE__; MISSING_TEST( "Test missing" );
			FAILED( "MISSING_TEST didn't throw TestMissing" );
		}
		catch( const TestMissing& e )
		{
			IS_EQUAL( "Test missing", e.Description() );
			IS_EQUAL( line, e.Line() );
			IS_EQUAL( filename, e.File() );
		}
	}

	
	//////////////////////////////////////////////////////////////////////////	
}

