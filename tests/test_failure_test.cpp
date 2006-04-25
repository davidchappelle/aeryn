
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

/** \file test_failure_test.cpp
*  \brief Declaration of TestFailureTest.
 */	

#include "test_failure_test.hpp"
#include <aeryn/test_failure.hpp>
#include <aeryn/test_funcs.hpp>
#include <string>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		/**	\brief Example failure message. */
		const std::string failureMsg	= "Test failed!";

		/**	\brief Example failure line. */
		const unsigned long line			= __LINE__;

		/**	\brief Example failure file. */
		const std::string file				= __FILE__;
	}
		
	//////////////////////////////////////////////////////////////////////////
	void TestFailureTest::BasicAccessor
			()
	{
		TestFailure testFailure( failureMsg, line, file.c_str() );
		IS_EQUAL( failureMsg, testFailure.Failure() );
		IS_EQUAL( line, testFailure.Line() );
		IS_EQUAL( file, testFailure.File() );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestFailureTest::CopyConstructor
		()
	{
		TestFailure testFailure( failureMsg, line, file.c_str() );
		TestFailure copy( testFailure );
		IS_EQUAL( failureMsg, copy.Failure() );
		IS_EQUAL( line, copy.Line() );
		IS_EQUAL( file, copy.File() );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestFailureTest::CopyAssignmentOperator
		()
	{
		TestFailure testFailure( failureMsg, line, file.c_str() );
		TestFailure copy( "", 0, "" );
		copy = testFailure;
		IS_EQUAL( failureMsg, copy.Failure() );
		IS_EQUAL( line, copy.Line() );
		IS_EQUAL( file, copy.File() );
	}

	//////////////////////////////////////////////////////////////////////////	
}


