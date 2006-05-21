
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
#include <aeryn/details/noncopyable.hpp>
#include <aeryn/report_factory.hpp>


namespace Aeryn
{	
	//////////////////////////////////////////////////////////////////////////
	class CommandLineParser;	

	// Forward declared so test_set_cont.hpp can stay private.
	class TestSetCont;

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
		/**	\brief A store for test sets. */
		std::auto_ptr< TestSetCont >	testSets_;	

		/**\ brief Report factory. */
		const ReportFactory reportFactory_;

	public:
		/**	\brief Default constructor. 
		 *
		 *	\param reportFactory Factory used to create reports. Default = ReportFactory.
		 */
		explicit TestRunner
			( const ReportFactory& reportFactory = ReportFactory() );

		/**	\brief Destructor 
		 *
		 *	Required to prevent warnings when using std::autoptr with gcc.
		 */
		~TestRunner();

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
		
		/**	\brief Runs all the tests with the default report.
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

		/**	\brief Runs the named test with the default report.
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
			(  const std::string& name, 
			   IReport& report ) const;	

		/**	\brief Runs the named test set with the default report.
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

		 /** \brief Runs the tests specified by the command line.
		  *
		  *	If no test or test sets are specified all test are run.
		  *
		  *	\param commandLine Command line parser..
		  *
		  *	\return 0 if all tests pass, -1 if any fail.
		  *	\throw TestSetNameNotFound if the test set name can't be found.
		  *	\throw DuplicateTestSetNameFound if the test set name specified is not unique.
		  */
		 int Run
			 ( const CommandLineParser& commandLine ) const;
		 
		 /** \brief Runs the tests specified by the command line with the specified report.
		  *
		  *	If no test or test sets are specified all test are run.
		  *
		  *	\param commandLine Command line parser..
		  *	\param report The report.
		  *	\return 0 if all tests pass, -1 if any fail.
		  *	\throw TestSetNameNotFound if the test set name can't be found.
		  *	\throw DuplicateTestSetNameFound if the test set name specified is not unique.
		  */
		 int Run
			 ( const CommandLineParser& commandLine,
			   IReport& report ) const;	
	};
}

#endif // AERYN_TEST_RUNNER_HPP
