
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

#include "test_set_runner.hpp"
#include "test_set_cont.hpp"
#include "comand_line_test_set_builder.hpp"
#include <aeryn/test_runner.hpp>
#include <aeryn/minimal_report.hpp>
#include <aeryn/terse_report.hpp>
#include <aeryn/verbose_report.hpp>
#include <aeryn/xcode_report.hpp>
#include <cassert>

namespace Aeryn
{
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
		if ( commandLine.TestCount() == 0 && commandLine.TestSetCount() == 0)
		{
			return Run( report );
		}

		TestSetCont testSets;
		CommandLineTestSetBuilder cltsb( commandLine, *testSets_.get(), testSets );
		TestSetRunner runner( testSets, report );
		return runner.Run();
	}	
}
