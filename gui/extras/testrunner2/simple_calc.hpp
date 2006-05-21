
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

/** \file simple_calc.hpp
 *  \brief SimpleCalc declaration.
 */	

#ifndef AERYN_TEST_SIMPLE_CALC_H
#define AERYN_TEST_SIMPLE_CALC_H

#include <aeryn/details/noncopyable.hpp>
#include <stdexcept>

namespace Aeryn
{
	/**	\brief Divide by zero exception. */
	class DivideByZero 
	{};
		
	/**	\brief A <i>very</i> simple calculator. */
	class SimpleCalc : private Utils::Noncopyable
	{
	public:
		/**	\brief Adds two numbers together and returns the result.
		 *
		 *	\param lhs The first number.
		 *	\param rhs The second number.
		 *	\return The result of adding the two numbers.
		 */
		static double Add( double lhs, double rhs );

		/**	\brief Subtracts one number from another and returns the result.
		 *
		 *	\param lhs The first number.
		 *	\param rhs The second number.
		 *	\return The result of subtracting the second number from the first.
		 */
		static double Subtract( double lhs, double rhs );

		/**	\brief Multiplies two numbers together and returns the result.
		 *
		 *	\param lhs The first number.
		 *	\param rhs The second number.
		 *	\return The result of multiplying the two numbers.
		 */
		static double Multiply( double lhs, double rhs );

		/**	\brief Divides one number by another and returns the result.
		 *
		 *	\param lhs The first number.
		 *	\param rhs The second number.
		 *	\return The result of dividing the first number by the second.
		 *	\throw DivideByZero if rhs is zero.
		 */
		static double Divide( double lhs, double rhs );

	private:
		/**	\brief Private constructor to prevent instantiation of class without
		 *	non-static member functions. */
		SimpleCalc();
	};
}

#endif // AERYN_TEST_SIMPLE_CALC_H
