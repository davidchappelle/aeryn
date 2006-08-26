
#include "test_load.hpp"
#include "load1.hpp"
#include "load2.hpp"
#include "load3.hpp"

#include <aeryn/test_runner.hpp>
#include <aeryn/exception.hpp>
#include <aeryn/command_line_parser.hpp>
#include <aeryn/use_name.hpp>

namespace
{
	using namespace Aeryn;
	using namespace Range;
	
	TestCase loadTests[] = 
	{	
		TestCase( "Load1: for loop", FunctionPtr( TestLoad, &Load1 ) ),
		TestCase( "Load2: while loop", FunctionPtr( TestLoad, &Load2 ) ),
		TestCase( "Load3: STL", FunctionPtr( TestLoad, &Load3 ) ),
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
		testRunner.Add( USE_NAME( loadTests ) );
		result = testRunner.Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}
