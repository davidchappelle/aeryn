
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

/** \file testrunner2\main.cpp
 *  \brief Test runner implementation for TestRegistry tests.
 */	

#include <aeryn/test_registry.hpp>

/**	\brief main for test runner implementation for TestRegistry tests.
 *
 *	Aeryn supports the ability to register tests in any file using the TestRegistry (singleton) class
 *	and it's associated macros. testrunner2 is an example project using TestRegistry and this is its
 *	main funtion.
 *
 *	\param argc An integer that contains the count of arguments that follow in argv. The argc parameter 
 *	is always greater than or equal to 1. 
 *	\param argv An array of null-terminated strings representing command-line arguments entered by the 
 *	user of the program.
 *	\return 0 if all tests pass, otherwise -1.
 */
int main(  int argc, char *argv[] )
{
	using namespace Aeryn;
	TestRunner::IReportPtr report( TestRunner::CreateReport( argc, argv ) );
	return TestRegistry::GetTestRunner().Run( *report.get() );
}
