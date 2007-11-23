/**************************************************************************
 * Filename: test_registry.cpp
 * Author:   Pete Goodliffe
 * Identity: $Id: $
 * Notice:   Copyright 2005 Pete Goodliffe. All rights reserved.
 *           Please see the COPYRIGHT file for more details.
 *************************************************************************/

#include <aeryn/test_registry.hpp>
#include <aeryn/test_runner.hpp>
#include <aeryn/exception.hpp>
#include <aeryn/command_line_parser.hpp>
#include <iostream>

/**
 * TODO - document me
 *      - changed testrunner2 example to use this lib
 *
 * This is Pete's main version based on Paul's testrunner implementation.
 * The following docs have been filtched from testrunner2\
 *
 *	\brief main for test runner implementation for TestRegistry tests.
 *
 *	Aeryn supports the ability to register tests in any file using the TestRegistry (singleton) class
 *	and its associated macros. testrunner2 is an example project using TestRegistry and this is its
 *	main funtion.
 *
 *	\param argv An array of null-terminated strings representing command-line arguments entered by the 
 *	user of the program.
 *	\return 0 if all tests pass, otherwise -1.
 */
int main(int /*argc*/, char *argv[])
{
	using namespace Aeryn;
	int result = -1;

	try
	{
		CommandLineParser commandLineParser( argv );
		result = TestRegistry::GetTestRunner().Run( commandLineParser );
	}
	catch( const Exception& e )
	{
		std::cout << e.what() << std::endl;
	}

	return result;
}
