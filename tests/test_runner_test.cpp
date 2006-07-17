
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

/** \file test_runner_test.cpp
 *  \brief Definition of TestRunnerTest.
 */	

#include "test_runner_test.hpp"
#include <aeryn/test_runner.hpp>
#include <aeryn/use_name.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/test_name_not_found.hpp>
#include <aeryn/test_set_name_not_found.hpp>
#include <aeryn/duplicate_test_name_found.hpp>
#include <aeryn/duplicate_test_set_name_found.hpp>
#include <aeryn/command_line_parser.hpp>
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

		/**	\brief Fake report object used to monitor tests. */
		class Report : public IReport
		{
		public:
			/**	\typedef Container type for test name store. */
			typedef std::vector< std::string > StoreType;

		private:
			/**	\brief Store for names of run tests. */
			StoreType store_;

			/**	\brief Number of tests run. */
			unsigned long testCount_;

			/**	\brief Number of tests sets run. */
			unsigned long testSetCount_;

			/**	\brief Store for the name of the test set that's run. */
			std::string testSetName_;
			
		public:
			/**	Constructor */
			explicit Report()
				: store_(),
				  testCount_(0),
				  testSetCount_(0),
				  testSetName_()
			{
			}

			/**	\brief Returns store of names of tests run.
			 *
			 *	\return Store of names of tests run.
			 */
			StoreType Store() const
			{
				return store_;
			}

			/**	\brief Returns the number of tests run.
			 *
			 *	\return Returns the number of tests run.
			 */
			unsigned long TestCount
				() const
			{
				return testCount_;
			}

			/**	\brief Returns the number of test sets run.
			 *
			 *	\return Returns the number of test sets run.
			 */
			unsigned long TestSetCount
				() const
			{
				return testSetCount_;
			}

			/**	\brief Returns the name of the test set run.
			*
			*	\return Returns the name of the test set run.
			*/
			std::string TestSetName
				() const
			{
				return testSetName_;
			}

			virtual void BeginTesting
				( const std::string&,
				  unsigned long )
			{
			}

			virtual void BeginTestSet
				( const std::string& testSetName )
			{
				testSetName_ = testSetName;
				++testSetCount_;
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
				( unsigned long testCount, 
				  unsigned long,
				  unsigned long )
			{
				testCount_ += testCount;
			}
		};

		/**	Set of ten test cases for use in RunByName tests. */
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

		/**	Test set for us in RunByTestSetName tests. */
		const TestCase testSet1[] = {	TestCase( "Test1", TestFunc ),
										TestCase( "Test2", TestFunc ),
										TestCase( "Test3", TestFunc ),
										TestCase( "Test4", TestFunc ),
										TestCase( "Test5", TestFunc ),
										TestCase() };

		/**	Test set for us in RunByTestSetName tests. */
		const TestCase testSet2[] = {	TestCase( "Test6", TestFunc ),
										TestCase( "Test7", TestFunc ),
										TestCase( "Test8", TestFunc ),
										TestCase( "Test9", TestFunc ),
										TestCase( "Test10", TestFunc ),
										TestCase() };

		/**	Test set for us in RunByTestSetName tests. */
		const TestCase testSet3[] = {	TestCase( "Test11", TestFunc ),
										TestCase( "Test12", TestFunc ),
										TestCase( "Test13", TestFunc ),
										TestCase( "Test14", TestFunc ),
										TestCase( "Test15", TestFunc ),
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

			IS_EQUAL( static_cast< unsigned int >( 5 ), report.TestCount() );
			IS_EQUAL( "tests", report.TestSetName() );
			Report::StoreType store = report.Store();
			IS_EQUAL(  static_cast< unsigned int >( 5 ) , static_cast< unsigned int >( store.size() ) );
			IS_EQUAL( "Test2", store[0] );
			IS_EQUAL( "Test4", store[1] );
			IS_EQUAL( "Test6", store[2] );
			IS_EQUAL( "Test8", store[3] );
			IS_EQUAL( "Test10", store[4] );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
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
			IS_EQUAL( "Failed to find \"Test11\"", e.what() );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
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
			IS_EQUAL( "Duplicate test name found: \"Test1\"", e.what() );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::RunByTestSetNameTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( "Test set 1", testSet1 );
			testRunner.Add( "Test set 2", testSet2 );
			testRunner.Add( "Test set 3", testSet3 );

			Report report;
			testRunner.RunByTestSetName( "Test set 2", report );

			IS_EQUAL( static_cast< unsigned int >( 5 ), report.TestCount() );
			IS_EQUAL( "Test set 2", report.TestSetName() );
			Report::StoreType store = report.Store();
			IS_EQUAL(  static_cast< unsigned int >( 5 ), static_cast< unsigned int >( store.size() ) );
			IS_EQUAL( "Test6", store[0] );
			IS_EQUAL( "Test7", store[1] );
			IS_EQUAL( "Test8", store[2] );
			IS_EQUAL( "Test9", store[3] );
			IS_EQUAL( "Test10", store[4] );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::RunByTestSetNameTestNotFoundTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( "Test set 1", testSet1 );
			testRunner.Add( "Test set 2", testSet2 );
			testRunner.Add( "Test set 3", testSet3 );

			Report report;
			testRunner.RunByTestSetName( "Test set 4", report );
			FAILED( "Succeeded in running unknown test set!" );
		}
		catch( const TestSetNameNotFound& e )
		{
			IS_EQUAL( "Failed to find \"Test set 4\"", e.what() );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::DuplicateTestSetNameFoundTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( "Test set 1", testSet1 );
			testRunner.Add( "Test set 2", testSet2 );
			testRunner.Add( "Test set 2", testSet3 );

			Report report;
			testRunner.RunByTestSetName( "Test set 2", report );
			FAILED( "Failed to find duplicate test set name!" );
		}
		catch( const DuplicateTestSetNameFound& e )
		{
			IS_EQUAL( "Duplicate test set name found: \"Test set 2\"", e.what() );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::ComandLineParserTestsTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( USE_NAME( tests ) );

			const char *argv[] = {	"commandline",
									"-t", "Test2",
									"-t", "Test4",
									"-t", "Test6",
									"-t", "Test8",
									"-t", "Test10",
									0 };

			CommandLineParser commandLineParser( argv );			
			Report report;
			testRunner.Run( commandLineParser, report );		

			Report::StoreType store = report.Store();
			IS_EQUAL(  static_cast< unsigned int >( 5 ) , static_cast< unsigned int >( store.size() ) );
			IS_EQUAL( "Test2", store[0] );
			IS_EQUAL( "Test4", store[1] );
			IS_EQUAL( "Test6", store[2] );
			IS_EQUAL( "Test8", store[3] );
			IS_EQUAL( "Test10", store[4] );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::ComandLineParserTestSetTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( "Test set 1", testSet1 );
			testRunner.Add( "Test set 2", testSet2 );
			testRunner.Add( "Test set 3", testSet3 );

			const char *argv[] = {	"commandline",
									"-ts", "Test set 2",
									0 };

			CommandLineParser commandLineParser( argv );			
			Report report;
			testRunner.Run( commandLineParser, report );		

			Report::StoreType store = report.Store();
			IS_EQUAL(  static_cast< unsigned int >( 5 ), static_cast< unsigned int >( store.size() ) );
			IS_EQUAL( "Test6", store[0] );
			IS_EQUAL( "Test7", store[1] );
			IS_EQUAL( "Test8", store[2] );
			IS_EQUAL( "Test9", store[3] );
			IS_EQUAL( "Test10", store[4] );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TestRunnerTest::ComandLineParserTestsAndTestSetsTest()
	{
		try
		{
			TestRunner testRunner;
			testRunner.Add( "Test set 1", testSet1 );
			testRunner.Add( "Test set 2", testSet2 );
			testRunner.Add( "Test set 3", testSet3 );

			const char *argv[] = {	"commandline",
									"-ts", "Test set 2",
									"-t", "Test7",
									"-t", "Test9",
									"-t", "Test1",
									"-t", "Test2",
									"-t", "Test13",
									"-t", "Test14",
									0 };

			CommandLineParser commandLineParser( argv );			
			Report report;
			testRunner.Run( commandLineParser, report );		

			Report::StoreType store = report.Store();
			IS_EQUAL(  static_cast< unsigned int >( 9 ), static_cast< unsigned int >( store.size() ) );
			IS_EQUAL(  static_cast< unsigned int >( 3 ), static_cast< unsigned int >( report.TestSetCount() ) );
			IS_EQUAL( "Test6", store[0] );
			IS_EQUAL( "Test7", store[1] );
			IS_EQUAL( "Test8", store[2] );
			IS_EQUAL( "Test9", store[3] );
			IS_EQUAL( "Test10", store[4] );
		}
		catch( const Exception& e )
		{
			FAILED( e.what() );
		}
	}
}


