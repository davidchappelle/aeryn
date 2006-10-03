
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
#include "load1.hpp"
#include "load2.hpp"

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
		TestCase( "Load1 (for loop) - TestLoadInc", FunctionPtr( TestLoadInc, &Load1 ) ),
		TestCase( "Load1 (for loop) - TestLoadDec", FunctionPtr( TestLoadDec, &Load1 ) ),
		TestCase( "Load1 (for loop) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &Load1 ) ),
		TestCase( "Load1 (for loop) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &Load1 ) ),
		TestCase()
	};	

	TestCase load2Tests[] = 
	{
		TestCase( "Load2 (stl) - TestLoadInc", FunctionPtr( TestLoadInc, &Load2 ) ),
		TestCase( "Load2 (stl) - TestLoadDec", FunctionPtr( TestLoadDec, &Load2 ) ),
		TestCase( "Load2 (stl) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &Load2 ) ),
		TestCase( "Load2 (stl) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &Load2 ) ),
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
		testRunner.Add( "Load1 (for loop)", load1Tests );
		testRunner.Add( "Load2 (stl)", load2Tests );
		result = testRunner.Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}
