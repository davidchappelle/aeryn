
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

/** \file test_func_test.hpp
 *  \brief Declaration of test function tests.
 */	

#ifndef AERYN_TEST_FUNC_TEST_HPP
#define AERYN_TEST_FUNC_TEST_HPP

namespace Aeryn
{
	/**	\brief Test for IS_TRUE being passed something true. */
	void IsTrueTest
		();

	/**	\brief Test for IS_TRUE being passed something false. */
	void IsTrueFailTest
		();

	/**	\brief Test for IS_FALSE being passed something false. */
	void IsFalseTest
		();

	/**	\brief Test for IS_FALSE being passed something true. */
	void IsFalseFailTest
		();

	/**	\brief Test for IS_EQUAL being passed two equal objects. */
	void IsEqualTest
		();

	/**	\brief Test for IS_EQUAL being passed two non-equal objects. */
	void IsEqualFailTest
		();

	/**	\brief Test for IS_NOT_EQUAL being passed two non-equal objects. */
	void IsNotEqualTest
		();

	/**	\brief Test for IS_NOT_EQUAL being passed two equal objects. */
	void IsNotEqualFailTest
		();

	/**	\brief Test for IS_EQUAL failure for non-streamable objects. */
	void IsEqualMissingOutputOperator
		();

	/**	\brief Test for IS_NOT_EQUAL failure for non-streamable objects. */
	void IsNotEqualMissingOutputOperator
		();

	/**	\brief Test for IS_EQUAL_DELTA being passed two equivilent doubles. */
	void IsEqualDeltaTest
		();

	/**	\brief Test for IS_EQUAL_DELTA being passed two non-equivilent doubles. */
	void IsEqualDeltaFailTest
		();

	/**	\brief Test for IS_NOT_EQUAL_DELTA being passed two non-equivilent doubles. */
	void IsNotEqualDeltaTest
		();

	/**	\brief Test for IS_NOT_EQUAL_DELTA being passed two equivilent doubles. */
	void IsNotEqualDeltaFailTest
		();

	/**	\brief FAILURE test. */
	void FailureTest
		();

	/**	\brief Test for MISSING_TEST test condition macro. */
	void MissingTestTest
		();

	//////////////////////////////////////////////////////////////////////////	
}

#endif //AERYN_TEST_FUNC_TEST_HPP
