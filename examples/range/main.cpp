
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
	
	TestCase load1Tests[] = 
	{
		TestCase( "Load1 (for loop) - TestLoadInc", FunctionPtr( TestLoadInc, &Load1 ) ),
		TestCase( "Load1 (for loop) - TestLoadDec", FunctionPtr( TestLoadDec, &Load1 ) ),
/*		TestCase( "Load1 (for loop) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &Load1 ) ),
		TestCase( "Load1 (for loop) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &Load1 ) ),*/
		TestCase()
	};	

	TestCase load2Tests[] = 
	{
		TestCase( "Load2 (while loop) - TestLoadInc", FunctionPtr( TestLoadInc, &Load2 ) ),
		TestCase( "Load2 (while loop) - TestLoadDec", FunctionPtr( TestLoadDec, &Load2 ) ),
		TestCase( "Load2 (while loop) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &Load2 ) ),
		TestCase( "Load2 (while loop) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &Load2 ) ),
		TestCase()
	};

	TestCase load3Tests[] = 
	{
		TestCase( "Load3 (stl) - TestLoadInc", FunctionPtr( TestLoadInc, &Load3 ) ),
		TestCase( "Load3 (stl) - TestLoadDec", FunctionPtr( TestLoadDec, &Load3 ) ),
		TestCase( "Load3 (stl) - TestLoadNegInc", FunctionPtr( TestLoadNegInc, &Load3 ) ),
		TestCase( "Load3 (stl) - TestLoadNegDec", FunctionPtr( TestLoadNegDec, &Load3 ) ),
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
	//	testRunner.Add( "Load2 (while loop)", load2Tests );
	//	testRunner.Add( "Load3 (stl)", load2Tests );
		result = testRunner.Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}
