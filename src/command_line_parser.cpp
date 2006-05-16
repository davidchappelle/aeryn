
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

/** \file comnand_line_parser.cpp
 *  \brief CommandLineParser definition.
 */	

#include <aeryn/command_line_parser.h>
#include <cassert>
#include <iostream>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		const std::string testSwitch( "-t" );
		const std::string testSetSwitch( "-ts" );
		const std::string reportSwitch( "-r" );	
	}
	
	//////////////////////////////////////////////////////////////////////////
	CommandLineParser::CommandLineParser
	( 
		int argc, 
		const char *argv[ ] 
	)
	: commandLine_(),
	  report_(),
	  tests_(),
	  testSets_()
	{
		assert( argc > 0 );

		if ( argc > 0)
		{
			commandLine_ = std::string( argv[0] );
		}

		int i = 0;
		while( i < argc )
		{
			std::string param( argv[i] );

			if ( testSwitch == param && GetNextParam( i, argc, argv, param ) )
			{
				tests_.push_back( param );
			}
			else if ( testSetSwitch == param && GetNextParam( i, argc, argv, param ) )
			{
				testSets_.push_back( param );
			}
			else if ( reportSwitch == param && GetNextParam( i, argc, argv, param ) )
			{
				report_ = param;				
			}

			++i;
		}	

	}

	//////////////////////////////////////////////////////////////////////////
	std::string CommandLineParser::CommandLine
		() const
	{
		return commandLine_;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string CommandLineParser::Report
		() const
	{
		return report_;
	}

	//////////////////////////////////////////////////////////////////////////
	CommandLineParser::ConstItr CommandLineParser::TestBegin
		() const
	{
		return tests_.begin();
	}

	//////////////////////////////////////////////////////////////////////////
	CommandLineParser::ConstItr CommandLineParser::TestEnd
		() const
	{
		return tests_.end();
	}

	//////////////////////////////////////////////////////////////////////////
	CommandLineParser::ConstItr CommandLineParser::TestSetBegin
		() const
	{
		return testSets_.begin();
	}

	//////////////////////////////////////////////////////////////////////////
	CommandLineParser::ConstItr CommandLineParser::TestSetEnd
		() const
	{
		return testSets_.end();
	}

	//////////////////////////////////////////////////////////////////////////
	bool CommandLineParser::GetNextParam
	( 
		int& i, 
		int argc, 
		const char *argv[ ], 
		std::string& param 
	)
	{
		bool result = false;
		
		if ( i != argc )
		{
			++i;
			param = std::string( argv[i] );
			result = true;
		}

		return result;		
	}
}

