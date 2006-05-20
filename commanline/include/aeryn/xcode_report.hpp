
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

/** \file xcode_report.hpp
 *  \brief XcodeReport declaration.
 */	

#ifndef AERYN_XCODE_REPORT_HPP
#define AERYN_XCODE_REPORT_HPP

#include <aeryn/verbose_report.hpp>
#include <fstream>

namespace Aeryn
{
	/**	\brief XCodeReport
	 *	
	 *	The XCode report uses a file based cookie to stop the tests begin run if the code has 
	 *	not been changed. It's templated so that it can take on the behavior of any of the other 
	 *	reports. By default it uses the verbose report. The XCode report is intended for use with
	 *	the apple mac IDE XCode.
	 *
     *	\author Thaddaues Froggley and Paul Grenyer
	 */
	//[THADDAUES] thinking about build system integration
	// - don't to run tests when nothing has changed
	//   so: drop "test pass cookie", and tell build system about it
	// - is this useful for more than Xcode?
	// - is there a better way to do this?
	// - dropping a file "cookie" orthoganal to report type.
	template< class BaseReportT = Aeryn::VerboseReport >
	class XcodeReport : public BaseReportT
	{
	public:
		/**	\brief Constructor.
		 *
		 *	\param out The output stream to write the report to.
		 *	\param cookieFileName Name of file used to store cookie.
		 */
		explicit XcodeReport
			( std::ostream& out, 
			  const std::string& cookieFileName  )
		: BaseReportT( out ),
		  mCookieFileName( cookieFileName )
		{
		}

		/**	\brief Called after all test sets and their associated test cases have been run.
		 *
		 *	\param testCount The number of test cases run.
		 *	\param failureCount The number of test cases that failed or resulted in an error.
		 */
		virtual void EndTesting
			( unsigned long testCount, 
			  unsigned long failureCount )
		{
			BaseReportT::EndTesting( testCount, failureCount, failureCount );
			
			if (!failureCount)
			{
				//drop cookie
				std::ofstream cookie( mCookieFileName.c_str() );
				cookie << "Passed: " << testCount << " tests\n";
			}
		}

	private:
		/**	\brief Name of file used to store cookie. */
		const std::string mCookieFileName;
	};	
}

#endif // AERYN_XCODE_REPORT_HPP
