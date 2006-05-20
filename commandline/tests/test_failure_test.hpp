
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

/** \file test_failure_test.hpp
 *  \brief Definition of TestFailureTest.
 */	

#ifndef AERYN_TEST_FAILURE_TEST_HPP
#define AERYN_TEST_FAILURE_TEST_HPP

namespace Aeryn
{
	/**	\brief TestFailure exception tests. */
	class TestFailureTest
	{
	public:
		/**	\brief Accessor tests. */
		static void BasicAccessor
			();

		/**	\brief Copy constructor tests. */
		static void CopyConstructor
			();

		/**	\brief Copy assignment operator tests. */
		static void CopyAssignmentOperator
			();

	private:
		/**	\brief Private constructor to prevent instantiation of class without
		 *	non-static member functions. 
		 */
		TestFailureTest();
	};
}

#endif // AERYN_TEST_FAILURE_TEST_HPP
