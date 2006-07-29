
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

/** \file command_line_parser.cpp
 *  \brief CommandLineParser definition.
 */	

#include <aeryn/command_line_parser.hpp>
#include <cassert>
#include <sstream>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		const std::string helpSwitch( "-h" );
		const std::string helpSwitchLong( "--help" );
		const std::string testSwitch( "-t" );
		const std::string testSwitchLong( "--test" );
		const std::string testSetSwitch( "-ts" );
		const std::string testSetSwitchLong( "--testset" );
		const std::string reportSwitch( "-r" );	
		const std::string reportSwitchLong( "--report" );
		const std::string noHeaderSwitch( "-nh" );
		const std::string noHeaderSwitchLong( "--noheader" );
		const std::string listTestsSwitch( "-lt" );
		const std::string listTestsSwitchLong( "--list-test-names" );
		const std::string listTestSetsSwitch( "-lts" );
		const std::string listTestSetsSwitchLong( "--list-test-set-names" );

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
	bool CommandLineParser::DisplayHeader
		() const
	{
		return showHeader_;
	}

	//////////////////////////////////////////////////////////////////////////
	bool CommandLineParser::ListTests
		() const
	{
		return listTests_;
	}

	//////////////////////////////////////////////////////////////////////////
	bool CommandLineParser::ListTestSets
			() const
	{
		return listTestSets_;
	}

	//////////////////////////////////////////////////////////////////////////
	bool CommandLineParser::ShowHelp
			 () const
	{
		return showHelp_;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string CommandLineParser::Help
			 () const
	{
		std::stringstream str;

		str << "Aeryn command line usage:\n\n";
        str << "    " << commandLine_ << " <options>\n\n";
        str << "Where <options> are:\n";
        str << "    -h   [ --help] Display this help text\n";
		str << "    -nh  [ --noheader] Suppresses Aeryn header\n";
        str << "    -t   [ --test] <test name> Run any test called <test name>\n";
        str << "    -ts  [ --testset] <set name> Run any test set called <set name>\n";
        str << "    -r   [ --report] <report type> Select report type\n";
		str << "    -lt  [ --list-test-names] Lists test names\n";
		str << "    -lts [ --list-test-set-names] Lists test set names\n";
		str << "\n";
        str << "Avilable report types:";
        str << "    minimal, verbose, terse, xcode\n";

		return str.str();
	}

	//////////////////////////////////////////////////////////////////////////
	CommandLineParser::SizeType CommandLineParser::TestCount
		() const
	{
		return tests_.size();
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
	CommandLineParser::SizeType CommandLineParser::TestSetCount
		() const
	{
		return testSets_.size();
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
	void CommandLineParser::Process
	( 
		const StringStore& commandArgs 
	)
	{
		if ( commandArgs.empty() )
		{
			return;
		}

		commandLine_ = commandArgs[0];

		if ( commandArgs.size() > 1 )
		{
			StringStore::const_iterator current = commandArgs.begin();
			StringStore::const_iterator end		= commandArgs.end();
			while( current != end )
			{
				std::string param( *current );

				if ( helpSwitch == param || helpSwitchLong == param )
				{
					showHelp_ = true;
				}
				else if ( noHeaderSwitch == param || noHeaderSwitchLong == param )
				{
					showHeader_ = false;
				}
				else if ( listTestsSwitch == param || listTestsSwitchLong == param )
				{
					listTests_ = true;
				}
				else if ( listTestSetsSwitch == param || listTestSetsSwitchLong == param )
				{
					listTestSets_ = true;
				}
				else if ( ( testSwitch == param || testSwitchLong == param ) && GetNextParam( current, end, param ) )
				{
					tests_.push_back( param );
				}
				else if ( ( testSetSwitch == param || testSetSwitchLong == param ) && GetNextParam( current, end, param ) )
				{
					testSets_.push_back( param );
				}
				else if ( ( reportSwitch == param || reportSwitchLong == param ) && GetNextParam( current, end, param ) )
				{
					report_ = param;				
				}
				
				if ( current != end )
				{
					++current;
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	bool CommandLineParser::GetNextParam
	( 
		StringStore::const_iterator& current, 
		const StringStore::const_iterator& end, 
		std::string& param
	) const
	{
		bool result = false;
		
		++current;
		
		if ( current != end )
		{
			param = *current;
			result = true;
		}

		return result;		
	}

}

