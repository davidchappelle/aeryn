
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
#include <algorithm>
#include <cassert>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		class ListTestsFunc
		{
		private:
			const bool listTests_;
			const bool listTestSets_;
			std::ostream& out_;

		public:
			ListTestsFunc
				( bool listTests,
				  bool listTestSets,
				  std::ostream& out )
			: listTests_( listTests ),
			  listTestSets_( listTestSets ),
			  out_( out )
			{
				if ( listTests_ && !listTestSets_ )
				{
					out_ << "Test list:\n";
				}
				else if ( !listTests_ && listTestSets_ )
				{
					out_ << "Test set list:\n";
				}
				else if ( listTests_ && listTestSets_ )
				{
					out_ << "Test and test set list:\n";
				}	

				out_ << "\n";
			}

			void operator()
				( const TestSetCont::ValueType& elem )
			{
				if ( listTestSets_ )
				{
					out_ << " - " << elem.second << "\n";
				}

				TestSetCont::TestCaseCont::const_iterator testIdx = elem.first.begin();
				TestSetCont::TestCaseCont::const_iterator testEnd = elem.first.end();

				for( ; testIdx != testEnd; ++testIdx )
				{
					if ( listTests_ )
					{
						if ( listTestSets_ )
						{
							out_ << " ";
						}
						
						out_ << " - " << testIdx->Name() << "\n";
					}
				}

				if ( listTestSets_ && listTests_ )
				{
					out_ << "\n";
				}
			}

		private:
			ListTestsFunc& operator=
				( const ListTestsFunc& );				  
		};


	}
	
	
	//////////////////////////////////////////////////////////////////////////
	TestRunner::TestRunner
		( const ReportFactory& reportFactory ) 
	: testSets_( new TestSetCont ),
	  reportFactory_( reportFactory ),
	  displayHeader_( true )
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
		return Run( *reportFactory_.Create( ReportFactory::DefaultTestName() ) );
	}
	
	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
	( 
		IReport& report
	) const
	{
		TestSetRunner runner( *testSets_, report, displayHeader_ );		
		return runner.Run();
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByName
		(  const std::string& name ) const
	{
		return RunByName( name, *reportFactory_.Create( ReportFactory::DefaultTestName() ) );
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
		testSets.AddTestSet( testSetName, FindTestByName( name, *testSets_, testSetName ) );
		TestSetRunner runner( testSets, report, displayHeader_ );
		return runner.Run();
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByTestSetName
	( 
		const std::string& name 
	) const
	{
		return RunByTestSetName( name, *reportFactory_.Create( ReportFactory::DefaultTestName() ) );
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::RunByTestSetName
	( 
		const std::string& name,
		IReport& report 
	) const
	{
		TestSetCont testSets;		
		testSets.AddTestSet( FindTestSetByName( name, *testSets_ ) );		
		TestSetRunner runner( testSets, report, displayHeader_ );
		return runner.Run();
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
	( 
		const CommandLineParser& commandLine 
	)
	{
		return Run( commandLine, *reportFactory_.Create( commandLine.Report() ) );
	}

	//////////////////////////////////////////////////////////////////////////
	int TestRunner::Run
	( 
		const CommandLineParser& commandLine,
		IReport& report 
	)
	{
		int result = -1;
		
		if ( commandLine.ListTests() || commandLine.ListTestSets() )
		{
			ListTestsFunc listTestsFunc( commandLine.ListTests(), commandLine.ListTestSets(), std::cout );
			std::for_each( testSets_->Begin(), testSets_->End(), listTestsFunc );
			result = 0;
		}
		else
		{
			displayHeader_ = commandLine.DisplayHeader();
		
			if ( commandLine.TestCount() == 0 && commandLine.TestSetCount() == 0)
			{
				return Run( report );
			}

			TestSetCont testSets;
			CommandLineTestSetBuilder cltsb( commandLine, *testSets_, testSets );
			TestSetRunner runner( testSets, report, displayHeader_ );
			result = runner.Run();
		}

		return result;
	}		
}
