
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

		if ( commandArgs.size() > 2 )
		{
			StringStore::const_iterator current = commandArgs.begin();
			StringStore::const_iterator end		= commandArgs.end();
			while( current != end )
			{
				std::string param( *current );
				
				if ( testSwitch == param && GetNextParam( current, end, param ) )
				{
					tests_.push_back( param );
				}
				else if ( testSetSwitch == param && GetNextParam( current, end, param ) )
				{
					testSets_.push_back( param );
				}
				else if ( reportSwitch == param && GetNextParam( current, end, param ) )
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

