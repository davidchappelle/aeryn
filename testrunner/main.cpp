
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

/** \file testrunner\main.cpp
 *  \brief Test runner implementation for Aeryn's static library based tests.
 */	

#include "../tests/add_tests.hpp"
#include <aeryn/test_runner.hpp>
#include <aeryn/test_name_not_found.hpp>

#include <iostream>
#include <string>
#include <memory>

/**	\brief main for Aeryn's static library based tests.
 *
 *	Dividing tests up into sets and putting them in static libraries allows each static library to be
 *	tested in isolation and linked into a single project to run all tests. All Aeryn's tests are in
 *	a single static library (in order to demonstrate this) which exposes a single public function that 
 *	takes a TestRunner reference and adds all of Aeryn's tests to it. 
 *
 *	This main function creates a test runner and calls the exposed function in Aeryn's static test 
 *	library to add its tests to it.
 *
 *	\param argc An integer that contains the count of arguments that follow in argv. The argc parameter 
 *	is always greater than or equal to 1. 
 *	\param argv An array of null-terminated strings representing command-line arguments entered by the 
 *	user of the program.
 *	\return 0 if all tests pass, otherwise -1.
 */
int main( int argc, char *argv[] )
{
	using namespace Aeryn;
	int result = -1;

	try
	{
		TestRunner testRunner;
		Aeryn::AddTests( testRunner );
	
		TestRunner::IReportPtr report( TestRunner::CreateReport( argc, argv ) );
		result = testRunner.Run( *report.get() );	
	}
	catch( const Exception& e )
	{
		std::cout << e.What() << std::endl;
	}

	return result;
}
