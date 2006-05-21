
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
#include "command_line_test_set_builder.hpp"
#include <aeryn/test_runner.hpp>
#include <cassert>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	TestRunner::TestRunner
		( const ReportFactory& reportFactory ) 
	: testSets_( new TestSetCont ),
	  reportFactory_( reportFactory )
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
		return Run( *reportFactory_.Create( ReportFactory::defaultTestName ).get() );
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
		return RunByName( name, *reportFactory_.Create( ReportFactory::defaultTestName ).get() );
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
		return RunByTestSetName( name, *reportFactory_.Create( ReportFactory::defaultTestName ).get() );
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
		return Run( commandLine, *reportFactory_.Create( commandLine.Report() ).get() );
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
