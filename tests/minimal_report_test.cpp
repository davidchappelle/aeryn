
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

/** \file minimal_report_test.cpp
 *  \brief Definition of MinimalReportTest.
 */	

#include "minimal_report_test.hpp"
#include <aeryn/test_funcs.hpp>
#include <aeryn/minimal_report.hpp>
#include <aeryn/platform.hpp>

namespace Aeryn
{
	namespace
	{
		namespace TestStrings
		{
			namespace MSVC
			{
				/**	\brief Expected output of the minimal report test for MSVC. */
				const std::string minimalOutput = 
					"Test Header\n" + std::string( 60, '-' )
					+"\n\n"
					"Test\t: Test 2\n\n"
					"myfile.cpp(100): Failure!"
					"\n" + std::string( 60, '-' ) + "\n"
					"\n"
					"Error\t: Error!\n"
					"\n" + std::string( 60, '-' ) + "\n"
					"\n"
					"Test\t: Missing test\n\n"
					"myfile.cpp(101): Missing test!"
					"\n" + std::string( 60, '-' ) + "\n"
					"\n"
					"Ran 4 tests, 1 Passed, 2 Failed, 1 Missing.\n"
					"\n";
			}

			namespace Other
			{
				/**	\brief Expected output of the minimal report test for "other" compilers. */
				const std::string minimalOutput = 
					"Test Header\n" + std::string( 60, '-' )
					+"\n"
					"\n"
					"Test\t: Test 2\n\n"
					"myfile.cpp:100: Failure!"
					"\n" + std::string( 60, '-' ) + "\n"
					"\n"
					"Error\t: Error!\n"
					"\n" + std::string( 60, '-' ) + "\n"
					"\n"
					"Test\t: Missing test\n\n"
					"myfile.cpp:101: Missing test!"
					"\n" + std::string( 60, '-' ) + "\n"
					"\n"
					"Ran 4 tests, 1 Passed, 2 Failed, 1 Missing.\n"
					"\n";
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReportTest
		()
	{
		std::stringstream out;
		MinimalReport report( out );
		
		report.BeginTesting( "Test Header\n", 3 );
		report.BeginTestSet( "Test Set 1" );

		report.BeginTest( "Test 1" );
		report.Pass( "Test 1" );
		report.EndTest( "Test 1" );

		report.BeginTest( "Test 2" );
		report.Failure( "Test 2", TestFailure( "Failure!", 100, "myfile.cpp" ) );
		report.EndTest( "Test 2" );

		report.EndTestSet( "Test Set 1" );
		report.BeginTestSet( "Test Set 2" );

		report.BeginTest( "" );
		report.Error( "", "Error!" );
		report.EndTest( "" );

		report.EndTestSet( "Test Set 2" );
		report.BeginTestSet( "Test Set 3" );

		report.BeginTest( "Test 3" );
		report.MissingTest( "Missing test", TestMissing( "Missing test!", 101, "myfile.cpp" ) );
		report.EndTest( "Test 3" );

		report.EndTestSet( "Test Set 3" );
		report.EndTesting( 4, 2, 1 );

		switch( COMPILER )
		{
		case MSVC:
			IS_EQUAL( TestStrings::MSVC::minimalOutput, out.str() );
			break;

		case Other:
		default:
			IS_EQUAL( TestStrings::Other::minimalOutput, out.str() );
			break;
		};
	}
	
	//////////////////////////////////////////////////////////////////////////		
}
