
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

/** \file test_runner_test.cpp
 *  \brief Definition of TestRunnerTest.
 */	

#include "test_runner_test.hpp"
#include <aeryn/test_runner.hpp>
#include <aeryn/use_name.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/test_name_not_found.hpp>
#include <aeryn/duplicate_test_name_found.hpp>
#include <iostream>
#include <string>
#include <vector>


namespace Aeryn
{
	namespace
	{
		/** Dummy test function. */
		void TestFunc()
		{
		}

		class Report : public IReport
		{
		public:
			typedef std::vector< std::string > StoreType;

		private:
			StoreType store_;
			
		public:
			StoreType Store() const
			{
				return store_;
			}

			virtual void BeginTesting
				( const std::string&,
				  unsigned long )
			{
			}

			virtual void BeginTestSet
				( const std::string& )
			{
			}

			virtual void BeginTest
				( const std::string& testName )
			{
				store_.push_back( testName );
			}

			virtual void Pass
				( const std::string& )
			{
			}

			virtual void Failure
				(  const std::string&,
				  const TestFailure& )
			{
			}

			virtual void MissingTest
				(  const std::string&,
				  const TestMissing& )
			{
			}

			virtual void Error
				( const std::string&,
				  const std::string& )
			{
			}

			virtual void EndTest
				( const std::string& )
			{
			}

			virtual void EndTestSet
				( const std::string& )
			{
			}

			virtual void EndTesting
				( unsigned long, 
				  unsigned long,
				  unsigned long )
			{
			}
		};

		const TestCase tests[] = {	TestCase( "Test1", TestFunc ),
									TestCase( "Test2", TestFunc ),
									TestCase( "Test3", TestFunc ),
									TestCase( "Test4", TestFunc ),
									TestCase( "Test5", TestFunc ),
									TestCase( "Test6", TestFunc ),
									TestCase( "Test7", TestFunc ),
									TestCase( "Test8", TestFunc ),
									TestCase( "Test9", TestFunc ),
									TestCase( "Test10", TestFunc ),
									TestCase() };
	}
	
	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::RunByNameTest()
	{		
		try
		{
			TestRunner testRunner;
			testRunner.Add( USE_NAME( tests ) );

			Report report;
			testRunner.RunByName( "Test2", report );
			testRunner.RunByName( "Test4", report );
			testRunner.RunByName( "Test6", report );
			testRunner.RunByName( "Test8", report );
			testRunner.RunByName( "Test10", report );

			Report::StoreType store = report.Store();
			IS_EQUAL(  5 , static_cast< unsigned int >( store.size() ) );
			IS_EQUAL( "Test2", store[0] );
			IS_EQUAL( "Test4", store[1] );
			IS_EQUAL( "Test6", store[2] );
			IS_EQUAL( "Test8", store[3] );
			IS_EQUAL( "Test10", store[4] );
		}
		catch( const Exception& e )
		{
			FAILED( e.What().c_str() );
		}

	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::RunByNameTestNotFoundTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( USE_NAME( tests ) );

			Report report;
			testRunner.RunByName( "Test11", report );
			FAILED( "Succeeded in running unknown test!" );
		}
		catch( const TestNameNotFound& e )
		{
			IS_EQUAL( "Failed to find \"Test11\"", e.What() );
		}
		catch( const Exception& e )
		{
			FAILED( e.What().c_str() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::DuplicateTestNameFoundTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( "Test set 1", tests );
			testRunner.Add( "Test set 2", TestCase( "Test1", TestFunc ) );

			Report report;
			testRunner.RunByName( "Test1", report );
			FAILED( "Failed to find duplicate test name!" );
		}
		catch( const DuplicateTestNameFound& e )
		{
			IS_EQUAL( "Duplicate test name found: \"Test1\"", e.What() );
		}
		catch( const Exception& e )
		{
			FAILED( e.What().c_str() );
		}
	}
}


