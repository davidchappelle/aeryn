
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

/** \file simple_calc_test.cpp
 *  \brief Definition of SimpleCalcTest. 
 */	

#include "simple_calc_test.hpp"
#include "simple_calc.hpp"
#include <aeryn/is_equal.hpp>
#include <aeryn/is_not_equal.hpp>
#include <aeryn/does_not_throw_exception.hpp>
#include <aeryn/throws_exception.hpp>
#include <aeryn/test_registry.hpp>


namespace Aeryn
{
	void SimpleCalcTest::AddTest()
	{
		IS_EQUAL( 4, SimpleCalc::Add( 2, 2 ) );
		IS_NOT_EQUAL( 3, SimpleCalc::Add( 2, 2 ) );
		IS_NOT_EQUAL( 5, SimpleCalc::Add( 2, 2 ) );
	}

	void SimpleCalcTest::SubtractTest()
	{
		IS_EQUAL( 5, SimpleCalc::Subtract( 10, 5 ) );
		IS_NOT_EQUAL( 4, SimpleCalc::Subtract( 10, 5 ) );
		IS_NOT_EQUAL( 6, SimpleCalc::Subtract( 10, 5 ) );
	}

	void SimpleCalcTest::MultiplyTest()
	{
		IS_EQUAL( 4, SimpleCalc::Multiply( 2, 2 ) );
		IS_NOT_EQUAL( 3, SimpleCalc::Multiply( 2, 2 ) );
		IS_NOT_EQUAL( 5, SimpleCalc::Multiply( 2, 2 ) );
	}

	void SimpleCalcTest::DivideTest()
	{
		IS_EQUAL( 2, SimpleCalc::Divide( 10, 5 ) );
		IS_NOT_EQUAL( 1, SimpleCalc::Divide( 10, 5 ) );
		IS_NOT_EQUAL( 3, SimpleCalc::Divide( 10, 5 ) );

		DOES_NOT_THROW_EXCEPTION( SimpleCalc::Divide( 10, 5 ) );
		THROWS_EXCEPTION( SimpleCalc::Divide( 10, 0 ), DivideByZero );
	}

	namespace
	{				
		/**	\brief Array of add and subtract tests. */
		TestCase addSubtractTests[] =
		{
			TestCase( USE_NAME( SimpleCalcTest::AddTest) ),
			TestCase( USE_NAME( SimpleCalcTest::SubtractTest) ),
			TestCase()
		};

		/**	\brief Array of multiply tests. */
		TestCase multiplyTest[] =
		{
			TestCase( USE_NAME( SimpleCalcTest::MultiplyTest) ),
			TestCase()
		};

		/**	\brief Array of divide tests. */
		TestCase divideTest[] =
		{
			TestCase( USE_NAME( SimpleCalcTest::DivideTest) ),
			TestCase()
		};

		/**	\brief Registers add and subtract tests.*/
		REGISTER_TESTS( addSubtractTests );
		
		/**	\brief Registers multiply tests.*/
		REGISTER_TESTS_WITH_NAME( "Multiply Test", multiplyTest );

		/**	\brief Registers divide tests.*/
		REGISTER_TESTS_USE_NAME( divideTest );
	}
}
