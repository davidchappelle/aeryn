
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

/** \file test_runner.cpp
 *  \brief TestRunner implementation.
 */	

#include "test_set_runner.h"
#include "test_set_cont.h"
#include <aeryn/test_runner.hpp>
#include <aeryn/minimal_report.hpp>
#include <aeryn/terse_report.hpp>
#include <aeryn/verbose_report.hpp>
#include <aeryn/xcode_report.hpp>
#include <aeryn/test_name_not_found.hpp>
#include <aeryn/test_set_name_not_found.hpp>
#include <aeryn/duplicate_test_name_found.hpp>
#include <aeryn/duplicate_test_set_name_found.hpp>
#include <aeryn/command_line_parser.h>
#include <cassert>
#include <algorithm>
#include <map>



namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
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
	}
	
	//////////////////////////////////////////////////////////////////////////
	TestRunner::IReportPtr TestRunner::CreateReport
	(
		int argc, 
		char *argv[] 
	)
	{
		std::auto_ptr< IReport > report( new MinimalReport );

		if ( argc == 2 )
		{
			report = CreateReport( argv[1] );
		}
		
		assert( report.get() );
		return report;
	}

	//////////////////////////////////////////////////////////////////////////
	TestRunner::IReportPtr TestRunner::CreateReport
	( 
		const std::string& reportName
	)
	{
		std::auto_ptr< IReport > report( new MinimalReport );
		
		if ( reportName == "terse"  )
		{
			report.reset( new TerseReport( std::cout ) );
		}
		else if ( reportName == "verbose" )
		{
			report.reset( new VerboseReport );
		}
		else if ( reportName == "xcode" )
		{
			report.reset( new XcodeReport<>( std::cout, "bin/TestPassCookie.txt" ) );
		}			
		
		return report;
	}
	
	//////////////////////////////////////////////////////////////////////////
	TestRunner::TestRunner
		() 
	: testSets_( new TestSetCont )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	TestRunner::~TestRunner
		()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const std::string& name, 
		const TestCase nullTerminatedArray[]
	)
	{
		testSets_->AddTests( name, nullTerminatedArray );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const TestCase nullTerminatedArray[] 
	)
	{
		testSets_->AddTests( nullTerminatedArray );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const std::string& name, 
		const TestCase& singleTestCase		
	)
	{
		testSets_->AddTest( name, singleTestCase );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const TestCase& singleTestCase 
	)
	{
		testSets_->AddTest( singleTestCase );
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
		() const
	{
		MinimalReport report;
		return Run( report );
	}
	
	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
	( 
		IReport& report
	) const
	{
		TestSetRunner runner( *testSets_.get(), report );		
		return runner.Run();
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByName
		(  const std::string& name ) const
	{
		MinimalReport report;
		return RunByName( name, report );
	}


	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByName
	(  
		const std::string& name, 
		IReport& report 
	) const
	{
		std::string testSetName;
		TestSetCont testSets;
		testSets.AddTestSet( testSetName, FindTestByName( name, *testSets_.get(), testSetName ) );
		TestSetRunner runner( testSets, report );
		return runner.Run();
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByTestSetName
	( 
		const std::string& name 
	) const
	{
		MinimalReport report;
		return RunByTestSetName( name, report );
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByTestSetName
	( 
		const std::string& name,
		IReport& report 
	) const
	{
		TestSetCont testSets;		
		testSets.AddTestSet( FindTestSetByName( name, *testSets_.get() ) );		
		TestSetRunner runner( testSets, report );
		return runner.Run();
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
	( 
		const CommandLineParser& commandLine 
	) const
	{
		TestRunner::IReportPtr report( CreateReport( commandLine.Report() ) );
		return Run( commandLine, *report.get() );
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
	( 
		const CommandLineParser& commandLine,
		IReport& report 
	) const
	{
		const CommandLineParser::SizeType testCount		= commandLine.TestCount();
		const CommandLineParser::SizeType testSetCount	= commandLine.TestSetCount();

		if ( testCount == 0 && testSetCount == 0)
		{
			return Run( report );
		}

		TestSetCont testSets;
		
		CommandLineParser::ConstItr current = commandLine.TestSetBegin();
		CommandLineParser::ConstItr end		= commandLine.TestSetEnd();
		for( ; current != end; ++current )
		{
			testSets.AddTestSet( FindTestSetByName( *current, *testSets_.get() ) );
		}

		typedef std::map< std::string, TestSetCont::TestCaseCont > TestCaseContMap;
		TestCaseContMap ts;

		current = commandLine.TestBegin();
		end		= commandLine.TestEnd();
		for( ; current != end; ++current )
		{
			std::string testSetName;
			TestCase test = FindTestByName( *current, *testSets_.get(), testSetName );			

			// If the test belongs to one of the test sets already added there is
			// no point in adding it again.
			if ( std::find(	commandLine.TestSetBegin(), 
							commandLine.TestSetEnd(),
							testSetName ) == commandLine.TestSetEnd() )
			{
				ts[ testSetName ].push_back( test );
			}
		}

		TestCaseContMap::const_iterator tsCurrent = ts.begin();
		TestCaseContMap::const_iterator tsEnd = ts.end();
		for( ; tsCurrent != tsEnd; ++tsCurrent )
		{
			testSets.AddTestSet( TestSetCont::TestSet( tsCurrent->second, tsCurrent->first ) );
		}

		TestSetRunner runner( testSets, report );
		return runner.Run();
	}

	
}



