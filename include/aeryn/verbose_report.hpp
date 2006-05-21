
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

/** \file verbose_report.hpp
 *  \brief VerboseReport declaration.
 */	

#ifndef AERYN_VERBOSE_REPORTER_HPP
#define AERYN_VERBOSE_REPORTER_HPP

#include <aeryn/ireport.hpp>
#include <ostream>
#include <iostream>

namespace Aeryn
{
	/**	\brief Verbose report.
	 *
	 *	The verbose report lists all test sets and test cases that are given a name. Those that are 
	 *	not named are not displayed as there is no useful information. Following the copyright 
	 *	message and the list of tests, the number of test cases run, the number of passes and number 
	 *	of failures are displayed.
	 *
	 *	If one or more test cases fail its failure message, the line the failure occurred on and the 
	 *	file the failure occurred in are displayed immediately below the test case name.
	 */
	class VerboseReport : public IReport
	{
	private:
		/**	\brief A reference to the output stream to write the report to. */
		std::ostream& out_;
				
	public:
		/**	\brief Returns the name of the report.
		 *
		 *	\return The name of the report.
		 */
		static std::string Name
			();

		/**	\brief Constructor.
		 *
		 *	\param out The output stream to write the report to.
		 */
		explicit VerboseReport
			( std::ostream& out = std::cerr );

		virtual void BeginTesting
			( const std::string& header,
			  unsigned long testCount );

		virtual void BeginTestSet
			( const std::string& testSetName );

		virtual void BeginTest
			( const std::string& testName );

		virtual void Pass
			( const std::string& testName );

		virtual void Failure
			(  const std::string& testName,
			const TestFailure& failure );

		virtual void MissingTest
			(  const std::string& testName,
			   const TestMissing& missingTest );

		virtual void Error
			( const std::string& testName,
			const std::string& errorDetails );

		virtual void EndTest
			( const std::string& testName );

		virtual void EndTestSet
			( const std::string& testSetName );

		virtual void EndTesting
			( unsigned long testCount, unsigned long failureCount, unsigned long missingCount );
	};
}

#endif // AERYN_VERBOSE_REPORTER_HPP
