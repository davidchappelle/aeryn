#include <aeryn/test_runner.hpp>
#include <aeryn/test_name_not_found.hpp>
#include <aeryn/command_line_parser.hpp>

#include <iostream>

int main( int, char *argv[] )
{
	using namespace Aeryn;
	int result = -1;

	try
	{
		TestRunner testRunner;

		CommandLineParser commandLineParser( argv );
		result = testRunner.Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}
