
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2006 Paul Grenyer
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

/** \file comnand_line_parser_test.cpp
 *  \brief CommandLineParserTest definition.
 */	

#include "command_line_parser_test.hpp"
#include <aeryn/command_line_parser.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/is_true.hpp>
#include <algorithm>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	void CommandLineParserTestDefaults
		()
	{
		const char *argv[] = { 0 };

		CommandLineParser commandLineParser( argv );

		IS_EQUAL( true, commandLineParser.DisplayHeader() );
		IS_EQUAL( false, commandLineParser.ListTests() );
		IS_EQUAL( false, commandLineParser.ListTestSets() );

		IS_EQUAL(	static_cast< unsigned int >( 0 ), commandLineParser.TestCount()  );
		IS_EQUAL(	static_cast< unsigned int >( 0 ), commandLineParser.TestSetCount() );
	}
	
	//////////////////////////////////////////////////////////////////////////
	void CommandLineParserTestShort
		()
	{
		const char *argv[] = {	"commandline",
								"-t", "test 1",
								"-t", "test 2",
								"--test", "test 3",
								"-ts", "test set 1",
								"--testset", "test set 2",
								"-r", "report",
								"-nh",
								"-lt",
								"-lts",
								0 };

		CommandLineParser commandLineParser( argv );

		const std::string expectedCommandLine( argv[0] );
		const std::string commandLine( commandLineParser.CommandLine() );
		IS_EQUAL( commandLine, expectedCommandLine );

		const std::string expectedReport( argv[12] );
		const std::string report( commandLineParser.Report() );
		IS_EQUAL( report, expectedReport );	

		IS_EQUAL( false, commandLineParser.DisplayHeader() );
		IS_EQUAL( true, commandLineParser.ListTests() );
		IS_EQUAL( true, commandLineParser.ListTestSets() );

		IS_EQUAL(	static_cast< unsigned int >( 3 ), commandLineParser.TestCount()  );
		IS_EQUAL(	static_cast< unsigned int >( 2 ), commandLineParser.TestSetCount() );

		int i = 0;
		CommandLineParser::ConstItr current = commandLineParser.TestBegin();
		for(i = 2; i < 8; i+=2 )
		{
			IS_EQUAL( argv[i], *current );
			 ++current;
		}
		IS_TRUE( commandLineParser.TestEnd() == current );

		current = commandLineParser.TestSetBegin();
		for(i = 8; i < 12; i+=2 )
		{
			IS_EQUAL( argv[i], *current );
			++current;
		}
		IS_TRUE( commandLineParser.TestSetEnd() == current );
	}

	//////////////////////////////////////////////////////////////////////////
	void CommandLineParserTestLong
		()
	{
		const char *argv[] = {	"commandline",
								"-t", "test 1",
								"--test", "test 2",
								"--test", "test 3",
								"--testset", "test set 1",
								"-ts", "test set 2",
								"--report", "report",
								"--noheader",
								"--list-test-names",
								"--list-test-set-names",
								0 };

		CommandLineParser commandLineParser( argv );

		const std::string expectedCommandLine( argv[0] );
		const std::string commandLine( commandLineParser.CommandLine() );
		IS_EQUAL( commandLine, expectedCommandLine );

		const std::string expectedReport( argv[12] );
		const std::string report( commandLineParser.Report() );
		IS_EQUAL( report, expectedReport );	

		IS_EQUAL( false, commandLineParser.DisplayHeader() );
		IS_EQUAL( true, commandLineParser.ListTests() );
		IS_EQUAL( true, commandLineParser.ListTestSets() );

		IS_EQUAL(	static_cast< unsigned int >( 3 ), commandLineParser.TestCount()  );
		IS_EQUAL(	static_cast< unsigned int >( 2 ), commandLineParser.TestSetCount() );

		int i = 0;
		CommandLineParser::ConstItr current = commandLineParser.TestBegin();
		for(i = 2; i < 8; i+=2 )
		{
			IS_EQUAL( argv[i], *current );
			 ++current;
		}
		IS_TRUE( commandLineParser.TestEnd() == current );

		current = commandLineParser.TestSetBegin();
		for(i = 8; i < 12; i+=2 )
		{
			IS_EQUAL( argv[i], *current );
			++current;
		}
		IS_TRUE( commandLineParser.TestSetEnd() == current );
	}
}
