
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

/** \file ireport.hpp
 *  \brief IReport declaration.
 */	

#ifndef AERYN_IREPORT_HPP
#define AERYN_IREPORT_HPP

#include <aeryn/details/noncopyable.hpp>
#include <string>

namespace Aeryn
{
	class TestFailure;
	class TestMissing;
	
	/**	\brief Interface for all Aeryn reports. */
	class IReport : private Utils::Noncopyable
	{
	public:
		/**	\brief Destructor. */
		virtual ~IReport
			() = 0;

		/**	\brief Called prior to the first test set.
		 *
		 *	\param header A std::string object containing the Aeryn header, including the copyright message.
		 *	\param testCount The number of test cases that will be run.
		 */
		virtual void BeginTesting
			( const std::string& header,
			  unsigned long testCount ) = 0;

		/**	\brief Called at the start of each test set.
		 *
		 *	\param testSetName The name of the test set that is about to be run.
		 */
		virtual void BeginTestSet
			( const std::string& testSetName ) = 0;

		/**	\brief Called prior to each test case
		 *
		 *	\param testName The name of the test case about to be run.	
		 */
		virtual void BeginTest
			( const std::string& testName ) = 0;

		/**	\brief Called immediately after each test case that passes.
		 *
		 *	\param testName The name the test case that passed.
		 */
		virtual void Pass
			( const std::string& testName ) = 0;

		/**	\brief Called immediately after each test case that fails.
		 *
		 *	\param testName The name the test case that failed.
		 *	\param failure A TestFailure object containing the details of the test case that failed.
		 */
		virtual void Failure
			(  const std::string& testName,
			   const TestFailure& failure ) = 0;

		/**	\brief Called to indicate that a test is missing and needs to be written.
		 *
		 *	\param testName The name the test case that failed.
		 *	\param missingTest A TestMissing object containing the details of the missing test.
		 */
		virtual void MissingTest
			(  const std::string& testName,
			   const TestMissing& missingTest ) = 0;

		/**	\brief Called immediately after each test case that results in an error.
		 *
		 *	\param testName The name the test case that cause an error.
		 *	\param errorDetails	A std::string describing the error caused by the test case.
		 */
		virtual void Error
			( const std::string& testName,
			  const std::string& errorDetails ) = 0;	

		/**	\brief Called after each test case.
		 *
		 *	\param testName The name of the test case that was just run.
		 */
		virtual void EndTest
			( const std::string& testName ) = 0;

		/**	\brief Called after each test set.
		 *
		 *	\param testSetName The name of the test set that was just run.
		 */
		virtual void EndTestSet
			( const std::string& testSetName ) = 0;

		/**	\brief Called after all test sets and their associated test cases have been run.
		 *
		 *	\param testCount The number of test cases run.
		 *	\param failureCount The number of test cases that failed or resulted in an error.
		 *	\param missingCount The number of missing tests.
		 */
		virtual void EndTesting
			( unsigned long testCount, 
			  unsigned long failureCount,
			  unsigned long missingCount ) = 0;
	};
}

#endif // AERYN_IREPORT_HPP
