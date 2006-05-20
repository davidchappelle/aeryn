
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
#include <numeric>
#include <ostream>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	class CommandLineParser;

	

	/**	\brief Default test set name. */
	static const std::string defaultTestSetName = "";

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

	

	

	/**	\brief TestSet container. */
	class TestSetCont : private Utils::Noncopyable
	{
	public:
		/**	\brief TestCase container type. */
		typedef std::vector< TestCase >					TestCaseCont;

		/**	\brief TestSet type. */
		typedef std::pair< TestCaseCont, std::string >	TestSet;		

	private:
		typedef std::vector< TestSet > CONT;
		CONT testSets_;

	public:
		typedef CONT::const_iterator const_iterator;
		typedef CONT::size_type size_type;

		explicit TestSetCont()
			: testSets_()
		{
		}

		/**	\brief Adds a test set and gives it a name. 
		 *
		 *	\param name The test set name.
		 *	\param nullTerminatedArray A null terminated array of TestCase's.
		 */
		void Add
			( const std::string& name,
			  const TestCase nullTerminatedArray[] )
		{
			TestCaseCont testSet;

			for( unsigned long i = 0; !nullTerminatedArray[i].IsNull(); ++i )
			{
				testSet.push_back( nullTerminatedArray[i] );
			}

			testSets_.push_back( TestSet( testSet, name ) );
		}

		/**	\brief Adds a test set.
		 *
		 *	\param nullTerminatedArray A null terminated array of TestCase's.
		 */
		void Add
			( const TestCase nullTerminatedArray[] )
		{
			Add( defaultTestSetName, nullTerminatedArray );
		}

		/**	\brief Adds a single test case and gives it a name. 
		 *
		 *	\param name The test case name.
		 *	\param singleTestCase A null terminated array of TestCase's.
		 */
		void Add
			( const std::string& name, 
			  const TestCase& singleTestCase )
		{
			TestCaseCont testSet;
			testSet.push_back( singleTestCase );
			testSets_.push_back( TestSet( testSet, name ) );
		}

		/**	\brief Adds a single test case.
		 *
		 *	\param singleTestCase A null terminated array of TestCase's.
		 */
		void Add
			( const TestCase& singleTestCase )
		{
			Add( defaultTestSetName, singleTestCase );
		}

		void Add
			( const TestSet& testSet )
		{
			testSets_.push_back( testSet );
		}

		void AddTestSet
			( const std::string& testSetName,
			  const TestCase& test )
		{
			TestCaseCont tests;
			tests.push_back( test );
			testSets_.push_back( TestSet( tests, testSetName ) );
		}

		/**	\brief Gives the number of test cases. */
		size_type TestCount
			() const
		{
			return std::accumulate(	testSets_.begin(), 
									testSets_.end(), 
									0, 
									AccumTestCount< TestCaseCont::size_type, TestSet > );		
		}

		const_iterator Begin
			() const
		{
			return testSets_.begin();
		}

		const_iterator End
			() const
		{
			return testSets_.end();
		}

		/**	\brief Finds a test by name.
		 *
		 *	\param name The name of the test to find.
		 *	\param testSetName A reference to a string to take the name of the test set
		 *	that the test belongs too.
		 *	\return The test if found otherwise TestCase().
		 */
		TestCase FindTest
		( 
			const std::string& name,
			std::string& testSetName 
		) const
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
						testSetName = currentTestSet->second;
						return *current;
					}
				}
			}

			return TestCase();
		}

		/**	\brief Determines if the specified test name is unique.
		 *
		 *	\param name The test name to search for.
		 *	\return true if the name is unique, otherwise false.
		 */
		bool IsTestNameUnique
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

		/**	\brief Finds a test set by name.
		 *
		 *	\param name The name of the test set to find.
		 *	\param testSet A reference to a TestSet object to take the test set if found.
		 *	\return True if the test set is found, otherwise false.
		 */
		bool FindTestSetByName
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


		/**	\brief Determines if the specified test set name is unique.
		 *
		 *	\param name The test set name to search for.
		 *	\return true if the name is unique, otherwise false.
		 */
		bool IsTestSetNameUnique
		( 
			const std::string& name 
		) const
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


	};
	
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

	private:
		static IReportPtr CreateReport
			( const std::string& reportName );
	};
}

#endif // AERYN_TEST_RUNNER_HPP
