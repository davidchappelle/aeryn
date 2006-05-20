
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

/** \file examples\customreport1\main.cpp
 *  \brief An example of a custom report.
 */	

#include <aeryn/test_runner.hpp>
#include <aeryn/minimal_report.hpp>
#include <aeryn/use_name.hpp>

/**	\brief A Custom report.
 *
 *	This report can be used as both an Aeryn report and as a context object. It inherits from
 *	Aeryn::MinimalReport and adds the ability to send messages to std::cout during test
 *	running.
 */
class CustomReport : public Aeryn::MinimalReport
{
public:
	/**	\brief Default constructor. */
	CustomReport()
	{
	}

	/**	\brief Copy constructor. */
	CustomReport( const CustomReport& )
	{
	}

	/**	\brief Writes to std::cout.
	 *
	 *	\param out The string to write.
	 */
	void Out( const std::string& out )
	{
		std::cout << out;
	}
};

/**	\brief Simple test function that writes full stops to the custom report. 
 *
 *	\param report Custom report context object.
 */
void TestOut( CustomReport& report )
{
	report.Out( "\n" );

	for( int i = 0; i < 10; ++i)
	{
		report.Out( "." );
	}

	report.Out( "\n" );
	report.Out( "\n" );
}

/**	\brief Simple main function using CustomReport and executing TestOut test. */
int main()
{
	using namespace Aeryn;

	TestRunner testRunner;
	CustomReport customReport;
	testRunner.Add( "Test Out", TestCase( USE_NAME( FunctionPtr( TestOut, customReport ) ) ) );
	
	return testRunner.Run( customReport );
}
