
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

/** \file terse_report.cpp
 *  \brief TerseReport implementation.
 */	

#include <aeryn/terse_report.hpp>
#include <aeryn/test_failure.hpp>
#include <aeryn/platform_report_output.hpp>

namespace Aeryn
{
	namespace
	{
		/**	\brief A string containing the separator to use in the report. */
		const std::string separator = std::string( 60, '-' ); 	
	}

	//////////////////////////////////////////////////////////////////////////
	std::string TerseReport::Name
		()
	{
		return "terse";
	}

	//////////////////////////////////////////////////////////////////////////
	TerseReport::TerseReport
	( 
		std::ostream& out,
		std::ostream& progress
	)
	: out_( out ), progress_( progress )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::BeginTesting
	( 
		const std::string& header,
		unsigned long 
	)
	{
		if ( !header.empty() )
		{
			out_ << header;
			out_ << separator << "\n";
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::BeginTestSet
	( 
		const std::string& 
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::BeginTest
	( 
		const std::string& 
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::Pass
	(
		const std::string&
	)
	{
		progress_ << ".";
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::Failure
	( 
		const std::string& testName,
		const TestFailure& failure
	)
	{
		progress_ << "F";
		WriteTestDetails( testName );	

		errorString_ << FormatFailure< COMPILER >::Out( failure );
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::MissingTest
	(  
		const std::string&,
		const TestMissing& 
	)
	{
		progress_ << "N";
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::Error
	( 
		const std::string& testName,
		const std::string& errorDetails 
	)
	{
		progress_ << "E";
		WriteTestDetails( testName );

		errorString_ << "Error\t: " << errorDetails << "\n";
		errorString_ << "\n";	
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::EndTest
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::EndTestSet
	(
		const std::string&
	)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::EndTesting
	(
		unsigned long testCount, 
		unsigned long failureCount,
		unsigned long missingCount
	)
	{
		out_ << "\n";
		
		if ( failureCount > 0 )
		{
			out_ << "\n";
			out_ << errorString_.str();
			out_ << separator << "\n";
		}
		
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

		out_ << ".\n";
	}

	//////////////////////////////////////////////////////////////////////////
	void TerseReport::WriteTestDetails
	( 
		const std::string& testName 
	)
	{
		errorString_ << separator << "\n";
		errorString_ << "\n";
			
		if ( !testName.empty() )
		{
			errorString_ << "Test\t: " << testName << "\n";
			errorString_ << "\n";	
		}
	}

	//////////////////////////////////////////////////////////////////////////	

}

