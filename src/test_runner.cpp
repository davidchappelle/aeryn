
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

#include <aeryn/test_runner.hpp>
#include <aeryn/test_failure.hpp>
#include <aeryn/minimal_report.hpp>
#include <aeryn/terse_report.hpp>
#include <aeryn/verbose_report.hpp>
#include <aeryn/xcode_report.hpp>
#include <aeryn/missing_test.hpp>
#include <aeryn/test_name_not_found.hpp>
#include <aeryn/test_set_name_not_found.hpp>
#include <aeryn/duplicate_test_name_found.hpp>
#include <aeryn/duplicate_test_set_name_found.hpp>
#include <aeryn/command_line_parser.h>

#include <numeric>
#include <cassert>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace 
	{
		/**	\brief Aeryn copyright message. */
		const std::string header =	"\n"
									"Aeryn 2.1.2 (c) Paul Grenyer 2005-2006\n"
									"http://www.aeryn.co.uk/\n";	

		/**	\brief Default test set name. */
		const std::string defaultTestSetName = "";


		/**	\brief Predicate used to count number of test cases.
		 *
		 *	\param total The total number of test cases counted so far.
		 *	\param testSet A test set to add to the count.
		 *	\return The new test case count.
		 */
		template< class SizeT, class ValueT >
		SizeT AccumTestCount
		( 
			SizeT total, 
			const ValueT& testSet  
		)
		{
			return total += testSet.first.size();
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
	: testSets_()
	{
		testSets_.reserve( 10 );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const std::string& name, 
		const TestCase nullTerminatedArray[]
	)
	{
		TestCaseCont testSet;

		for( unsigned long i = 0; !nullTerminatedArray[i].IsNull(); ++i )
		{
			testSet.push_back( nullTerminatedArray[i] );
		}

		testSets_.push_back( TestSet( testSet, name ) );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const TestCase nullTerminatedArray[] 
	)
	{
		Add( defaultTestSetName, nullTerminatedArray );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const std::string& name, 
		const TestCase& singleTestCase		
	)
	{
		TestCaseCont testSet;
		testSet.push_back( singleTestCase );
		testSets_.push_back( TestSet( testSet, name ) );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::Add
	( 
		const TestCase& singleTestCase 
	)
	{
		Add( defaultTestSetName, singleTestCase );
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
		const unsigned long testCout	= TestCount();
		unsigned long failureCount		= 0;
		unsigned long missingCount		= 0;
		report.BeginTesting( header, testCout );

		TestSetCont::const_iterator currentTestSet	= testSets_.begin();
		TestSetCont::const_iterator endTestSet		= testSets_.end();

		for( ; currentTestSet != endTestSet; ++currentTestSet )
		{
			RunTestSet( failureCount, missingCount, *currentTestSet, report );			
		}
		
		report.EndTesting( testCout, failureCount, missingCount );

		return failureCount != 0 ? -1 : 0;
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
		const unsigned long testCout	= TestCount();
		unsigned long failureCount		= 0;
		unsigned long missingCount		= 0;

		report.BeginTesting( header, testCout );

		TestCase test = FindTest( name );
		if ( !test.IsNull() )
		{
			if ( !IsTestNameUnique( name ) )
			{
				throw DuplicateTestNameFound( name );
			}
			
			RunTest( failureCount, missingCount, test, report );
		}
		else
		{
			throw TestNameNotFound( name );
		}

		report.EndTesting( testCout, failureCount, missingCount );
		
		return failureCount != 0 ? -1 : 0;
	}

	//////////////////////////////////////////////////////////////////////////
	unsigned long TestRunner::TestCount
		() const
	{
		return std::accumulate(	testSets_.begin(), 
								testSets_.end(), 
								0, 
								AccumTestCount< TestCaseCont::size_type, TestSet > );		
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
		const unsigned long testCout	= TestCount();
		unsigned long failureCount		= 0;
		unsigned long missingCount		= 0;

		report.BeginTesting( header, testCout );

		TestSet testSet;
		if ( FindTestSetByName( name, testSet ) )
		{
			if ( !IsTestSetNameUnique( name ) )
			{
				throw DuplicateTestSetNameFound( name );
			}
			
			RunTestSet( failureCount, missingCount, testSet, report );
		}
		else
		{
			throw TestSetNameNotFound( name );
		}

		report.EndTesting( testCout, failureCount, missingCount );

		return failureCount != 0 ? -1 : 0;
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::RunTestSet
	( 
		unsigned long& failureCount,
		unsigned long& missingCount,
		const TestSet& testSet,
		IReport& report 
	) const
	{
		report.BeginTestSet( testSet.second );

		TestCaseCont::const_iterator current	= testSet.first.begin();
		TestCaseCont::const_iterator end		= testSet.first.end();

		for( ; current != end; ++current )
		{
			RunTest( failureCount, missingCount, *current, report );
		}

		report.EndTestSet( testSet.second );
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

		int result = 0;
		CommandLineParser::ConstItr current = commandLine.TestBegin();
		CommandLineParser::ConstItr end		= commandLine.TestEnd();
		for( ; current != end; ++current )
		{
			if ( RunByName( *current, report ) == -1 )
			{
				result = -1;
			}
		}

		current = commandLine.TestSetBegin();
		end		= commandLine.TestSetEnd();
		for( ; current != end; ++current )
		{
			if ( RunByTestSetName( *current, report ) )
			{
				result = -1;
			}
		}

		return result;
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunner::RunTest
	( 
		unsigned long& failureCount,
		unsigned long& missingCount,
		const TestCase& test,
		IReport& report 
	) const
	{
		report.BeginTest( test.Name() );

		switch( RunTest( test, report ) )
		{
		case FAILED:
			++failureCount;
			break;

		case PASSED:
			break;

		case MISSING:
			++missingCount;
			break;

		default:
			assert( !"Unknown result type." );
		};				

		report.EndTest( test.Name() );
	}

	//////////////////////////////////////////////////////////////////////////
	TestRunner::Result TestRunner::RunTest
	(
		const TestCase& test,
		IReport& report 
	) const
	{
		Result result = FAILED;
		
		try
		{
			test.Run();
			report.Pass( test.Name() );
			result = PASSED;
		}
		catch( const TestFailure& e )
		{
			report.Failure( test.Name(), e );
		}
		catch( const TestMissing& e )
		{
			report.MissingTest( test.Name(), e );
			result = MISSING;
		}
		catch( const std::exception& e )
		{
			report.Error( test.Name(), e.what() );
		}
		catch( ... )
		{
			report.Error( test.Name(), "!!! Unknown Error !!!" );
		}	

		return result;
	}	

	//////////////////////////////////////////////////////////////////////////
	TestCase TestRunner::FindTest
		( const std::string& name ) const
	{
		TestSetCont::const_iterator currentTestSet	= testSets_.begin();
		TestSetCont::const_iterator endTestSet		= testSets_.end();

		for( ; currentTestSet != endTestSet; ++currentTestSet )
		{
			TestCaseCont::const_iterator current	= currentTestSet->first.begin();
			TestCaseCont::const_iterator end		= currentTestSet->first.end();

			for( ; current != end; ++current )
			{
				if ( name == current->Name() )
				{
					return *current;
				}
			}
		}
		
		return TestCase();
	}

	//////////////////////////////////////////////////////////////////////////
	bool TestRunner::IsTestNameUnique
	( 
		const std::string& name 
	) const
	{
		TestCaseCont::size_type count = 0;
		
		TestSetCont::const_iterator currentTestSet	= testSets_.begin();
		TestSetCont::const_iterator endTestSet		= testSets_.end();

		for( ; currentTestSet != endTestSet; ++currentTestSet )
		{
			TestCaseCont::const_iterator current	= currentTestSet->first.begin();
			TestCaseCont::const_iterator end		= currentTestSet->first.end();

			for( ; current != end; ++current )
			{
				if ( name == current->Name() )
				{
					++count;
				}
			}
		}

		return count <= 1;
	}

	//////////////////////////////////////////////////////////////////////////
	bool TestRunner::FindTestSetByName
	( 
		const std::string& name, 
		TestSet& testSet 
	) const
	{
		TestSetCont::const_iterator current	= testSets_.begin();
		TestSetCont::const_iterator end		= testSets_.end();

		for(; current != end; ++current )
		{
			if ( name == current->second )
			{
				testSet = *current;
				return true;
			}
		}
		
		return false;
	}


	//////////////////////////////////////////////////////////////////////////
	bool TestRunner::IsTestSetNameUnique
		( const std::string& name ) const
	{
		TestSetCont::size_type count = 0;

		TestSetCont::const_iterator current	= testSets_.begin();
		TestSetCont::const_iterator end		= testSets_.end();

		for( ; current != end; ++current )
		{
			if ( name == current->second )
			{
				++count;
			}		
		}

		return count <= 1;
	}

	//////////////////////////////////////////////////////////////////////////	
}


