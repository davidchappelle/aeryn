
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

/** \file minimal_report.cpp
 *  \brief MinimalReport implementation.
 */	

#include <aeryn/minimal_report.hpp>
#include <aeryn/test_failure.hpp>
#include <aeryn/platform_report_output.hpp>
#include <aeryn/missing_test.hpp>
#include <cassert>

namespace Aeryn
{
	namespace
	{
		/**	\brief A string containing the separator to use in the report. */
		const std::string separator = std::string( 60, '-' ); 	
	}

	//////////////////////////////////////////////////////////////////////////
	std::string MinimalReport::Name
		()
	{
		return "minimal";
	}

	//////////////////////////////////////////////////////////////////////////
	MinimalReport::MinimalReport
	( 
		std::ostream& out /* = std::err */
	)
	: out_( out )
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::BeginTesting
	( 
		const std::string& header,
		unsigned long 
	)
	{
		out_ << header;		
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::BeginTestSet
	( 
		const std::string& 
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::BeginTest
	( 
		const std::string& 
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::Pass
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::Failure
	( 
		const std::string& testName,
		const TestFailure& failure
	)
	{
		WriteTestDetails( testName );	
		out_ << FormatFailure< COMPILER >::Out( failure );
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::MissingTest
	(  
		const std::string& testName,
		const TestMissing& missingTest 
	)
	{
		WriteTestDetails( testName );

		out_ << FormatFailure< COMPILER >::Out(	missingTest.Description(), 
												missingTest.Line(), 
												missingTest.File().c_str() );
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::Error
	( 
		const std::string& testName,
		const std::string& errorDetails 
	)
	{
		WriteTestDetails( testName );

		out_ << "Error\t: " << errorDetails << "\n";
		out_ << "\n";	
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::EndTest
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::EndTestSet
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void MinimalReport::EndTesting
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
	void MinimalReport::WriteTestDetails
	( 
		const std::string& testName 
	)
	{
		out_ << separator << "\n";
		out_ << "\n";
		
		if ( !testName.empty() )
		{
			out_ << "Test\t: " << testName << "\n";
			out_ << "\n";	
		}
	}

	//////////////////////////////////////////////////////////////////////////	
}
