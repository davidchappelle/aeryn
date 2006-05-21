
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

/** \file simple_calc_test.hpp
 *  \brief Declaration of SimpleCalcTest.
 */	

#ifndef AERYN_TEST_SIMPLE_CALC_TEST_H
#define AERYN_TEST_SIMPLE_CALC_TEST_H

#include <aeryn/details/noncopyable.hpp>

namespace Aeryn
{
	/**	\brief SimpleCalc tests. */
	class SimpleCalcTest : private Utils::Noncopyable
	{
	public:
		/**	\brief Test for SimpleCalc's Add member. */
		static void AddTest();

		/**	\brief Test for SimpleCalc's Subtract member. */
		static void SubtractTest();

		/**	\brief Test for SimpleCalc's Multiply member. */
		static void MultiplyTest();

		/**	\brief Test for SimpleCalc's Divide member. */
		static void DivideTest();

	private:
		/**	\brief Private constructor to prevent instantiation of class without
		 *	non-static member functions. 
		 */
		SimpleCalcTest();
	};
}

#endif // AERYN_TEST_SIMPLE_CALC_TEST_H
