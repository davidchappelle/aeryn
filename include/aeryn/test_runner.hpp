
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

/** \file test_runner.hpp
 *  \brief TestRunner declaration.
 */	

#ifndef AERYN_TEST_RUNNER_HPP
#define AERYN_TEST_RUNNER_HPP

#ifdef _MSC_VER
#pragma warning ( disable : 4150 )
#endif // _MSC_VER

#include <aeryn/test_case.hpp>
#include <aeryn/ireport.hpp>
#include <aeryn/details/noncopyable.hpp>
#include <vector>
#include <ostream>

namespace Aeryn
{
	/**	\brief Stores and runs all tests.
	 *
	 *	Test cases must be added to a test runner in order to be run.
	 *
	 *	Once an instance of TestRunner has bee created, test cases can be added to it. There are basically two ways of 
	 *	adding tests cases: one at a time or any number as an array. Along with the test case(s) a name for the test set 
	 *	(one or more test cases added together) can also be added. If the test set name is not specified it defaults to 
	 *	a blank string.
	 *
	 *	<b>Adding a Single Test Case</b>
	 *
	 *	To add a single test case to a test runner, simply pass it to TestRunner's add member function with or without 
	 *	a test set name. For example:
	 *
	 *		<code>testRunner.Add( "HHGTTG", TestCase( USE_NAME( TestForTheMeaningOfLife ) ) );</code>
	 *
	 *	or
	 *
	 *		<code>testRunner.Add( TestCase( USE_NAME( TestForTheMeaningOfLife ) ) ); </code>
	 *
	 *	<b>Adding an Array of Test Cases</b>
	 *
	 *	To add an array of test cases to a test runner, simply pass it to TestRunner's Add member function with or 
	 *	without a test set name. For example:
	 *
	 *	<pre><code>
	 *
	 *	TestCase calculatorTests[] =
	 *	{
	 *		TestCase( "Basics", 
	 *		Incarnate( &CalculatorTest::TestBasics ) ),
	 *		TestCase( "Variables",
	 *		Incarnate( &CalculatorTest::TestVariables ) ),
	 *		TestCase( "Compound",
	 *		Incarnate( &CalculatorTest::TestCompound ) ),
	 *		TestCase()
	 *	};
     *
	 *	...
	 *
	 *	testRunner.Add( "Calculator", calculatorTests );
	 *	</code></pre>
	 *
	 *	or
	 *
	 *	<pre><code>
	 *
	 *	TestCase calculatorTests[] =
	 *	{
	 *		TestCase( "Basics", 
	 *		Incarnate( &CalculatorTest::TestBasics ) ),
	 *		TestCase( "Variables",
	 *		Incarnate( &CalculatorTest::TestVariables ) ),
	 *		TestCase( "Compound",
	 *		Incarnate( &CalculatorTest::TestCompound ) ),
	 *		TestCase()
	 *	};
	 *
	 *	...
	 *
	 * testRunner.Add( calculatorTests );
	 *	</code></pre>
	 *	The test case array must be terminated by a default constructed TestCase. This is so that the test 
	 *	runner can detect when it has reached the end of the array.
	 */
	class TestRunner : private Utils::Noncopyable
	{
	private:
		/**	\brief TestCase container type. */
		typedef std::vector< TestCase >					TestCaseCont;

		/**	\brief TestSet type. */
		typedef std::pair< TestCaseCont, std::string >	TestSet;

		/**	\brief TestSet container. */
		typedef std::vector< TestSet >					TestSetCont;	

		/**	\brief Result of running test indicator. */
		enum Result
		{
			FAILED,
			PASSED,
			MISSING
		};

		/**	\brief A store for test sets. */
		TestSetCont										testSets_;				

	public:
		/**	\brief Report smart pointer.
		 *
		 *	Used to automatically manage dynamically allocated report objects.
		 */
		typedef std::auto_ptr< IReport > IReportPtr;
		
		/**	\brief Creates a report based on command line parameters.
		 *
		 *	Aeryn includes an easy way to run different reports depending on the first command line argument 
		 *	passed to the test application at runtime. This is achieved using the CreateReport 
		 *	function. For example:
		 *
		 *	<pre><code>
		 *	int main( int argc, char *argv[] )
		 *	{
		 *		using namespace Aeryn;
		 *
		 *		TestRunner testRunner;
		 *		Aeryn::AddTests( testRunner );
		 *
		 *		TestRunner::IReportPtr report( TestRunner::CreateReport( argc, argv) );
		 *		return testRunner.Run( *report.get() );
		 *	}
		 *	</code></pre>
		 *
		 *	The command line argument options are: <code>terse</code>, <code>verbose</code>, <code>xcode</code>.
		 *
		 *	\param argc An integer that contains the count of arguments that follow in argv. The argc parameter is always greater than or equal to 1. 
		 *	\param argv An array of null-terminated strings representing command-line arguments entered by the user of the program.
		 *	\return An IReportPtr pointing to an instance of a report.
		 */
		static IReportPtr CreateReport
			( int argc, char *argv[] );

		/**	\brief Default constructor. */
		explicit TestRunner
			();

		/**	\brief Adds a test set and gives it a name. 
		 *
		 *	\param name The test set name.
		 *	\param nullTerminatedArray A null terminated array of TestCase's.
		 */
		void Add
			( const std::string& name,
			  const TestCase nullTerminatedArray[] );

		/**	\brief Adds a test set.
		 *
		 *	\param nullTerminatedArray A null terminated array of TestCase's.
		 */
		void Add
			( const TestCase nullTerminatedArray[] );

		/**	\brief Adds a single test case and gives it a name. 
		 *
		 *	\param name The test case name.
		 *	\param singleTestCase A null terminated array of TestCase's.
		 */
		void Add
			( const std::string& name, 
			  const TestCase& singleTestCase );

		/**	\brief Adds a single test case.
		 *
		 *	\param singleTestCase A null terminated array of TestCase's.
		 */
		void Add
			( const TestCase& singleTestCase );
		
		/**	\brief Runs all the tests with the default report (minimal).
		 *
		 *	\return 0 if all tests pass, -1 if any fail.
		 */
		int Run
			() const;
		
		/**	\brief Runs all the tests with the specified report.
		 *
		 *	\param report The report.
		 *	\return 0 if all tests pass, -1 if any fail.
		 */
		int Run
			(  IReport& report ) const;	

		/**	\brief Runs the named test with the default report (minimal).
		*
		*	\param name The name of the test to run.
		*	\return 0 if all tests pass, -1 if any fail.
		*	\throw TestNameNotFound if the test name can't be found.
		*	\throw DuplicateTestNameFound if the test name specified is not unique.
		*/
		int RunByName
			(  const std::string& name ) const;	
		
		/**	\brief Runs the named test the test with the specified report.
		 *
		 *	\param name The name of the test to run.
		 *	\param report The report.
		 *	\return 0 if all tests pass, -1 if any fail.
		 *	\throw TestNameNotFound if the test name can't be found.
		 *	\throw DuplicateTestNameFound if the test name specified is not unique.
		 */
		int RunByName
			(  const std::string& name, IReport& report ) const;	

		/**	\brief Runs the named test set with the specified report.
		 *
		 *	\param name The name of the test set to run.
		 *	\return 0 if all tests pass, -1 if any fail.
		 *	\throw TestSetNameNotFound if the test set name can't be found.
		 *	\throw DuplicateTestSetNameFound if the test set name specified is not unique.
		 */
		int RunByTestSetName
			( const std::string& name ) const;
		
		/**	\brief Runs the named test set with the specified report.
		 *
		 *	\param name The name of the test set to run.
		 *	\param report The report.
		 *	\return 0 if all tests pass, -1 if any fail.
		 *	\throw TestSetNameNotFound if the test set name can't be found.
		 *	\throw DuplicateTestSetNameFound if the test set name specified is not unique.
		 */
		 int RunByTestSetName
			( const std::string& name,
			  IReport& report ) const;

	private:
		/**	\brief Gives the number of test cases. */
		unsigned long TestCount
			() const;

		/**	\brief Runs a test set and updates test counters.
		 *
		 *	\param failureCount A counter for failed tests.
		 *	\param missingCount A counter for missing tests.
		 *	\param testSet The test set to run.
		 *	\param report The report the results are written to.
		 */
		void RunTestSet
			( unsigned long& failureCount,
			  unsigned long& missingCount,
			  const TestSet& testSet,
			  IReport& report ) const;
		
		/**	\brief Runs a test case and updates test counters.
		 *
		 *	\param failureCount A counter for failed tests.
		 *	\param missingCount A counter for missing tests.
		 *	\param test The test case to run.
		 *	\param report The report the results are written to.
		 */
		void RunTest
			( unsigned long& failureCount,
			  unsigned long& missingCount,
			  const TestCase& test,
			  IReport& report ) const;
		
		/**	\brief Runs a test case.
		 *
		 *	\param test The test case to run.
		 *	\param report The report the results are written to.
		 *	\return true PASS if tests passed, MISSING if test is missing otherwise FAILED.
		 */
		Result RunTest
			( const TestCase& test,
			  IReport& report ) const;

		/**	\brief Finds a test by name.
		 *
		 *	\param name The name of the test to find.
		 *	\return The test if found otherwise TestCase().
		 */
		TestCase FindTest
			( const std::string& name ) const;

		/**	\brief Determines if the specified test name is unique.
		 *
		 *	\param name The test name to search for.
		 *	\return true if the name is unique, otherwise false.
		 */
		bool IsTestNameUnique
			( const std::string& name ) const;

		/**	\brief Finds a test set by name.
		 *
		 *	\param name The name of the test set to find.
		 *	\param testSet A reference to a TestSet object to take the test set if found.
		 *	\return True if the test set is found, otherwise false.
		*/
		bool FindTestSetByName
			( const std::string& name, 
			  TestSet& testSet ) const;

		/**	\brief Determines if the specified test set name is unique.
		 *
		 *	\param name The test set name to search for.
		 *	\return true if the name is unique, otherwise false.
		 */
		bool IsTestSetNameUnique
			( const std::string& name ) const;
	};
}

#endif // AERYN_TEST_RUNNER_HPP
