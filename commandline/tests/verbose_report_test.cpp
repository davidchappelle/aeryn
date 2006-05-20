
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

/** \file verbose_report_test.cpp
 *  \brief Definition of VerboseReportTest.
 */	

#include "verbose_report_test.hpp"
#include <aeryn/test_funcs.hpp>
#include <aeryn/verbose_report.hpp>
#include <aeryn/platform.hpp>
#include <fstream>

namespace Aeryn
{
	namespace
	{
		namespace TestStrings
		{
			namespace MSVC
			{
				/**	\brief Expected output of the verbose report test for MSVC. */
				const std::string verboseOutput = 			
					"Test Header\n" + std::string( 60, '-' ) +
					"\n\n"
					"Test Set : Test Set 1\n"
					"\n"
					" - Test 1\n"
					" - Test 2\n"
					"myfile.cpp(100): Failure!"
					"\n"
					" - Test 3\n"
					"\n"
					"Error\t: Error!\n"
					"\n"
					"\n"
					" - Test 4\n"
					"myfile.cpp(101): Missing test!"
					"\n" + std::string( 60, '-' ) + "\n\n"
					"Ran 4 tests, 1 Passed, 2 Failed, 1 Missing.\n"
					"\n";
			}			

			namespace Other
			{
				/**	\brief Expected output of the verbose report test for "other" compilers. */
				const std::string verboseOutput = 			
					"Test Header\n" + std::string( 60, '-' ) +
					"\n\n"
					"Test Set : Test Set 1\n"
					"\n"
					" - Test 1\n"
					" - Test 2\n"
					"myfile.cpp:100: Failure!"
					"\n"
					" - Test 3\n"
					"\n"
					"Error\t: Error!\n"
					"\n"
					"\n"
					" - Test 4\n"
					"myfile.cpp:101: Missing test!"
					"\n" + std::string( 60, '-' ) + "\n\n"
					"Ran 4 tests, 1 Passed, 2 Failed, 1 Missing.\n"
					"\n";
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReportTest
		()
	{
		std::stringstream out;
		VerboseReport report( out );
		
		report.BeginTesting( "Test Header\n", 3 );
		report.BeginTestSet( "Test Set 1" );

		report.BeginTest( "Test 1" );
		report.Pass( "Test 1" );
		report.EndTest( "Test 1" );

		report.BeginTest( "Test 2" );
		report.Failure( "Test 2", TestFailure( "Failure!", 100, "myfile.cpp" ) );
		report.EndTest( "Test 2" );

		report.EndTestSet( "Test Set 1" );
		report.BeginTestSet( "" );

		report.BeginTest( "Test 3" );
		report.Error( "Test 3", "Error!" );
		report.EndTest( "Test 3" );

		report.BeginTest( "Test 4" );
		report.MissingTest( "Missing test", TestMissing( "Missing test!", 101, "myfile.cpp" ) );
		report.EndTest( "Test 4" );

		report.EndTestSet( "" );
		report.EndTesting( 4, 2, 1 );

		switch( COMPILER )
		{
		case MSVC:
			IS_EQUAL( TestStrings::MSVC::verboseOutput, out.str() );
			break;

		case Other:
		default:
			IS_EQUAL( TestStrings::Other::verboseOutput, out.str() );
			break;
		};
		
	}
	
	//////////////////////////////////////////////////////////////////////////		
}

