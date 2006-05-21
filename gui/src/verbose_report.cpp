
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

/** \file verbose_report.cpp
 *  \brief VerboseReport implementation.
 */	

#include <aeryn/verbose_report.hpp>
#include <aeryn/test_failure.hpp>
#include <aeryn/platform_report_output.hpp>
#include <aeryn/missing_test.hpp>

namespace Aeryn
{
	namespace
	{
		/**	\brief A string containing the separator to use in the report. */
		const std::string separator = std::string( 60, '-' ); 	
	}

	//////////////////////////////////////////////////////////////////////////
	std::string VerboseReport::Name
		()
	{
		return "verbose";
	}

	//////////////////////////////////////////////////////////////////////////
	VerboseReport::VerboseReport
	( 
		std::ostream& out /* = std::cerr */
	)
	: out_( out )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::BeginTesting
	( 
		const std::string& header,
		unsigned long 
	)
	{
		out_ << header;		
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::BeginTestSet
	( 
		const std::string& testSetName 
	)
	{		
		if ( !testSetName.empty() )
		{
			out_ << separator << "\n\n";
			out_ << "Test Set : "<< testSetName << "\n\n";
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::BeginTest
	( 
		const std::string& testName 
	)
	{
		if ( !testName.empty() )
		{
			out_ << " - " << testName << "\n";
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::Pass
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::Failure
	( 
		const std::string&,
		const TestFailure& failure
	)
	{
		out_ << FormatFailure< COMPILER >::Out( failure );
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::MissingTest
	(  
		const std::string&,
		const TestMissing& missingTest 
	)
	{
		out_ << FormatFailure< COMPILER >::Out(	missingTest.Description(), 
												missingTest.Line(), 
												missingTest.File().c_str() );
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::Error
	( 
		const std::string&,
		const std::string& errorDetails 
	)
	{
		out_ << "\n";
		out_ << "Error\t: " << errorDetails << "\n";
		out_ << "\n";	

		out_ << "\n";
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::EndTest
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::EndTestSet
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void VerboseReport::EndTesting
	(
		unsigned long testCount, 
		unsigned long failureCount,
		unsigned long missingCount
	)
	{
		out_ << separator << "\n\n";

		out_ << "Ran " << testCount << " test";
		if ( testCount != 1 )
		{
			out_ << "s";
		}

		out_ << ", ";
		out_ << testCount - failureCount - missingCount << " Passed, ";
		out_ << failureCount << " Failed";

		if ( missingCount > 0)
		{
			out_ << ", " << missingCount << " Missing";
		}

		out_ << ".\n\n";
	}

	//////////////////////////////////////////////////////////////////////////	
}

