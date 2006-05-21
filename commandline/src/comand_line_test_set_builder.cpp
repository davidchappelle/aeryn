
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

/** \file comand_line_test_set_builder.cpp
 *  \brief Definition of TestSetCont.
 */

#include "comand_line_test_set_builder.hpp"
#include <aeryn/duplicate_test_name_found.hpp>
#include <aeryn/duplicate_test_set_name_found.hpp>
#include <aeryn/test_set_name_not_found.hpp>
#include <aeryn/test_name_not_found.hpp>
#include <algorithm>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	TestCase FindTestByName
	( 
		const std::string& name,
		const TestSetCont& testSets,
		std::string &testSetName
	) 
	{			
		TestCase test = testSets.FindTest( name, testSetName );
		if ( !test.IsNull() )
		{
			if ( !testSets.IsTestNameUnique( name ) )
			{
				throw DuplicateTestNameFound( name );
			}				
		}
		else
		{
			throw TestNameNotFound( name );
		}

		return test;
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetCont::TestSet FindTestSetByName
	( 
		const std::string& name,
		const TestSetCont& testSets
	) 
	{
		TestSetCont::TestSet testSet;
		if ( testSets.FindTestSetByName( name, testSet ) )
		{
			if ( !testSets.IsTestSetNameUnique( name ) )
			{
				throw DuplicateTestSetNameFound( name );
			}			
		}
		else
		{
			throw TestSetNameNotFound( name );
		}

		return testSet;
	}

	//////////////////////////////////////////////////////////////////////////
	CommandLineTestSetBuilder::CommandLineTestSetBuilder
	( 
		const CommandLineParser& commandLine,
		const TestSetCont& testSets,
		TestSetCont& testSetsToRun 
	)
	: commandLine_( commandLine ),
	  testSets_( testSets ),
	  testSetsToRun_( testSetsToRun )
	{
		AddTestSets();
		AddTests();				
	}

	//////////////////////////////////////////////////////////////////////////
	void CommandLineTestSetBuilder::AddTestSets()
	{
		CommandLineParser::ConstItr current = commandLine_.TestSetBegin();
		CommandLineParser::ConstItr end		= commandLine_.TestSetEnd();
		for( ; current != end; ++current )
		{
			testSetsToRun_.AddTestSet( FindTestSetByName( *current, testSets_ ) );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void CommandLineTestSetBuilder::AddTests()
	{
		TestCaseContMap ts = GenerateTestTestSets();

		TestCaseContMap::const_iterator tsCurrent = ts.begin();
		TestCaseContMap::const_iterator tsEnd = ts.end();
		for( ; tsCurrent != tsEnd; ++tsCurrent )
		{
			testSetsToRun_.AddTestSet( TestSetCont::TestSet( tsCurrent->second, tsCurrent->first ) );
		}
	}	

	//////////////////////////////////////////////////////////////////////////
	CommandLineTestSetBuilder::TestCaseContMap CommandLineTestSetBuilder::GenerateTestTestSets() const
	{
		TestCaseContMap testSets;

		CommandLineParser::ConstItr current = commandLine_.TestBegin();
		CommandLineParser::ConstItr end		= commandLine_.TestEnd();
		for( ; current != end; ++current )
		{
			std::string testSetName;
			TestCase test = FindTestByName( *current, testSets_, testSetName );			

			// If the test belongs to one of the test sets already added there is
			// no point in adding it again.
			if ( std::find(	commandLine_.TestSetBegin(), 
				commandLine_.TestSetEnd(),
				testSetName ) == commandLine_.TestSetEnd() )
			{
				testSets[ testSetName ].push_back( test );
			}
		}

		return testSets;
	}

	//////////////////////////////////////////////////////////////////////////	
}
