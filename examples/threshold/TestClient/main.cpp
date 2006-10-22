
#include "../ThresholdTests/add_tests.hpp"

#include <aeryn/test_name_not_found.hpp>
#include <aeryn/command_line_parser.hpp>

int main( int, char *argv[] )
{
	using namespace Aeryn;
	int result = -1;

	try
	{
		TestRunner testRunner;
		Threshold::Tests::AddTests( testRunner );
		CommandLineParser commandLineParser( argv );
		result = testRunner.Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}

