
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

/** \file simple_date_test.hpp
 *  \brief SimpleDateTest declaration.
 */	

#ifndef UTILITY_TEST_SIMPLE_DATE_TEST_HEADER
#define UTILITY_TEST_SIMPLE_DATE_TEST_HEADER

//-----------------------------------------------------------------------------
namespace utility
{
	/**	\brief utility tests. */
	namespace test
	{
		/**	\brief simple_date tests. */
		class SimpleDateTest
		{
		public:
			/**	\brief Tests basic functionality. */
			static void BasicTest();

			/**	\brief Tests exceptions. */
			static void ExceptionTest();

			/**	\brief Tests is_leap-year. */
			static void IsLeapYearTest();

			/**	\brief Tests days of the week. */
			static void DayOfWeekTest();

			/**	\brief Tests intervale. */
			static void IntervalTest();

			/**	\brief Tests operators. */
			static void OperatorTests();

			/**	\brief Tests to_iso_date. */
			static void ToIsoDateTest();

			/**	\brief Empty date test. */
			static void EmptyDateTest();

		private:
			/**	\brief Private constructor to prevent instantiation of class without
			 *	non-static member functions. 
			 */
			SimpleDateTest();
		};
	}
}

//-----------------------------------------------------------------------------
#endif // UTILITY_TEST_SIMPLE_DATE_TEST_HEADER
