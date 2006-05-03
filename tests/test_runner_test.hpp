
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

/** \file test_runner_test.hpp
*  \brief Declaration of TestRunnerTest.
*/	

#ifndef AERYN_TEST_RUNNER_TEST_H
#define AERYN_TEST_RUNNER_TEST_H

namespace Aeryn
{
	/**	\brief TestRunner tests */
	class TestRunnerTest
	{
	public:
		/** \brief Tests run by name functionality. */
		static void RunByNameTest();

		/** \brief Tests run by name functionality when the test name specified doesn't exist. */
		static void RunByNameTestNotFoundTest();

		/** \brief Tests the DulicateTestNameFound exception. */
		static void DuplicateTestNameFoundTest();

	private:
		/**	\brief Private constructor to prevent instantiation of class without
		 *	non-static member functions. 
		 */
		TestRunnerTest();
	};
}


#endif // AERYN_TEST_RUNNER_TEST_H
