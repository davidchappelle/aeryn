
#include "../dlltests/add_tests.hpp"
#include <aeryn/test_runner.hpp>
#include <aeryn/command_line_parser.hpp>
#include <aeryn/exception.hpp>

int main( int, char* argv[] )
{
	using namespace Aeryn;

	int result = 0;
	
	try
	{
		CommandLineParser commandLine( argv );
		TestRunner testRunner;
		DynamicLibrary::AddTests( testRunner, commandLine.CommandLine() );		
		result = testRunner.Run( commandLine );
	}
	catch( const Exception& e )
	{
		std::cout << e.What() << "\n";
	}

	return result;
}