
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2006 Paul Grenyer
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

#include "test_load.hpp"
#include "load_closed_range1.hpp"
#include "load_closed_range2.hpp"

#include <aeryn/test_runner.hpp>
#include <aeryn/exception.hpp>
#include <aeryn/command_line_parser.hpp>
#include <aeryn/use_name.hpp>

namespace
{
	using namespace Aeryn;
	using namespace Range;
	
	TestCase load1Tests[] = 
	{
		TestCase( "LoadClosedRange1 (for loop) - TestLoadInc", FunctionPtr( TestLoadInc, &LoadClosedRange1 ) ),
		TestCase( "LoadClosedRange1 (for loop) - TestLoadDec", FunctionPtr( TestLoadDec, &LoadClosedRange1 ) ),
		TestCase( "LoadClosedRange1 (for loop) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &LoadClosedRange1 ) ),
		TestCase( "LoadClosedRange1 (for loop) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &LoadClosedRange1 ) ),
		TestCase()
	};	

	TestCase load2Tests[] = 
	{
		TestCase( "LoadClosedRange2 (stl) - TestLoadInc", FunctionPtr( TestLoadInc, &LoadClosedRange2 ) ),
		TestCase( "LoadClosedRange2 (stl) - TestLoadDec", FunctionPtr( TestLoadDec, &LoadClosedRange2 ) ),
		TestCase( "LoadClosedRange2 (stl) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &LoadClosedRange2 ) ),
		TestCase( "LoadClosedRange2 (stl) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &LoadClosedRange2 ) ),
		TestCase()
	};
}

int main( int, char *argv[] )
{
	using namespace Aeryn;
	int result = -1;

	try
	{
		TestRunner testRunner;
		CommandLineParser commandLineParser( argv );
		testRunner.Add( "LoadClosedRange1 (for loop)", load1Tests );
		testRunner.Add( "LoadClosedRange2 (stl)", load2Tests );
		result = testRunner.Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}
