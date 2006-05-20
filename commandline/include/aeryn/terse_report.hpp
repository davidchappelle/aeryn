
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

/** \file terse_report.hpp
 *  \brief TerseReport declaration.
 */	

#ifndef AERYN_TERSEREPORTER_H
#define AERYN_TERSEREPORTER_H

#include <aeryn/ireport.hpp>
#include <ostream>
#include <iostream>
#include <sstream>

namespace Aeryn
{
	/**	\brief Terse Report.
	 *
	 *	The terse report (contributed by Pete Goodliffe) is based on the CPPUnit reporting system and 
	 *	displays the Aeryn copyright message followed by a full stop (period) for each successful test, 
	 *	an F for failed tests, an E for errors and an N for missing tests followed by the number of 
	 *	passes and number of failures. 
	 *
	 *	If one or more test cases fail its name is displayed along with the test condition failure 
	 *	message, the line the failure occurred on and the file the failure occurred in after all the 
	 *	tests have run. Again, the number of test cases run, the number of passes and the number of 
	 *	failures is displayed.
	 *
	 *	\author Peter Goodliffe and Paul Grenyer.
	 */
	class TerseReport : public IReport
	{
	private:
		/**	\brief A reference to the output stream to write the main report to. */
		std::ostream		&out_;

		/**	\brief A reference to the output stream to write the report progress (".", "F", etc) to. */
		std::ostream		&err_;

		/**	\brief A buffer for the main report which is written to out_ when the tests are complete. */
		std::stringstream	errorString_;
				
	public:
		/**	\brief Constructor.
		 *
		 *	\param out The output stream to write the main report to. 
		 *	\param err The output stream to write the report progress (".", "F", etc) to. 
		 */
		explicit TerseReport
			( std::ostream& out = std::cerr,
			  std::ostream& err = std::cerr );

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

	private:
		/**	\brief Writes the details of a failed test to the output stream.
		 *
		 *	\param testName The name of the test that failed.
		 */
		void WriteTestDetails
			( const std::string& testName );
	};
}

#endif // AERYN_TERSEREPORTER_H
