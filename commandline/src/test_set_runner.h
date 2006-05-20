
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

/** \file test_set_runner.hpp
 *  \brief TestSetRunner declaration.
 */	

#ifndef AERYN_TEST_SET_RUNNER_H
#define AERYN_TEST_SET_RUNNER_H

#include <aeryn/details/noncopyable.hpp>
#include <aeryn/test_runner.hpp> // this must go.

namespace Aeryn
{
	/**	\brief Runs test sets. */
	class TestSetRunner : private Utils::Noncopyable
	{
	private:
		/**	\brief Result of running test indicator. */
		enum Result
		{
			/**	\brief Test failed. */
			FAILED,

			/**	\brief Test passed. */
			PASSED,

			/**	\brief Missing test. */
			MISSING
		};

		/**	\brief Reference to the test sets to be run. */
		const TestSetCont& testSets_;

		/**	\brief Reference to the report to use when running the tests. */
		IReport& report_;

	public:
		/**	\brief Constructor.
		 *
		 *	\param testSets The test sets to run.
		 *	\param report The report to use when running the tests.
		 */
		explicit TestSetRunner
			( const TestSetCont& testSets, 
			  IReport& report );

		/**	\brief Runs test sets.
		 *
		 *	\return 0 if all tests pass, -1 if any fail.
		 */
		int Run
			();

	private:
		/**	\brief TestCaseCont helper. */
		typedef TestSetCont::TestCaseCont TestCaseCont;

		/**	\brief TestSet helper. */
		typedef TestSetCont::TestSet TestSet;


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
		( 
			unsigned long& failureCount,
			unsigned long& missingCount,
			const TestCase& test,
			IReport& report 
		) const;

		/**	\brief Runs a test case.
		 *
		 *	\param test The test case to run.
		 *	\param report The report the results are written to.
		 *	\return true PASS if tests passed, MISSING if test is missing otherwise FAILED.
		 */
		Result RunTest
		(
			const TestCase& test,
			IReport& report 
		) const;
	};
}

#endif // AERYN_TEST_SET_RUNNER_H
