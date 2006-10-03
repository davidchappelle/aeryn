
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
