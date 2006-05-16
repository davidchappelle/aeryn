
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

#include "command_line_parser_test.h"
#include <aeryn/command_line_parser.h>
#include <aeryn/is_equal.hpp>
#include <aeryn/is_true.hpp>
#include <algorithm>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	void CommandLineParserTest
		()
	{
		const int argc = 13;
		const char *argv[] = {	"commandline",
								"-t", "test 1",
								"-t", "test 2",
								"-t", "test 3",
								"-ts", "test set 1",
								"-ts", "test set 2",
								"-r", "report" };

		CommandLineParser commandLineParser( argc, argv );

		const std::string expectedCommandLine( argv[0] );
		const std::string commandLine( commandLineParser.CommandLine() );
		IS_EQUAL( commandLine, expectedCommandLine );

		const std::string expectedReport( argv[12] );
		const std::string report( commandLineParser.Report() );
		IS_EQUAL( report, expectedReport );	

		IS_EQUAL(	static_cast< int >( 3 ), 
					static_cast< int >(	std::distance(	commandLineParser.TestBegin(), 
														commandLineParser.TestEnd() ) ) );

		IS_EQUAL(	static_cast< int >( 2 ), 
					static_cast< int >(	std::distance(	commandLineParser.TestSetBegin(), 
														commandLineParser.TestSetEnd() ) ) );

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
