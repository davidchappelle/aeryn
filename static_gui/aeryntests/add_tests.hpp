
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

/** \file add_tests.hpp
 *  \brief AddTest declaration.
 */	

#ifndef AERYN_ADD_TESTS_HPP
#define AERYN_ADD_TESTS_HPP

#include <aeryn/iadd_tests.hpp>

namespace Aeryn
{
	/**	\brief Adds Aeryn's tests to the supplied test runner.
	 *
	 *	Dividing tests up into sets and putting them in static libraries allows each static library to be
	 *	tested in isolation and linked into a single project to run all tests. All Aeryn's tests are in
	 *	a single static library (in order to demonstrate this) which exposes a single public function that 
	 *	takes a TestRunner reference and adds all of Aeryn's tests to it. 
	 *
	 *	This is the function that adds all of Aeryn's static library tests to a test runner.
	 *
	 *	\param testRunner The test runner to add the tests too.
	 */
	void AddTests
		( Aeryn::IAddTests& testRunner );
}

#endif // AERYN_ADD_TESTS_HPP
