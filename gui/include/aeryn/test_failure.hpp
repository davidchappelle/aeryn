
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

/** \file test_failure.hpp
 *  \brief TestFailure declaration.
 */	

#ifndef AERYN_TEST_FAILURE_HPP
#define AERYN_TEST_FAILURE_HPP

#include <string>

namespace Aeryn
{
	/**	\brief Test failure exception.
	 *
	 *	Thrown when a test fails.
	 */
	class TestFailure
	{
	private:
		/**	\brief The test failure message. */
		std::string	failure_;

		/**	\brief The line where the test failed. */
		unsigned long line_;

		/**	\brief The file in which the test failed. */
		const char*	file_;

	public:
		/**	\brief Constructor.
		 *
		 *	\param failure The test failure message.
		 *	\param line The line where the test failed.
		 *	\param file The file in which the test failed.
		 */
		TestFailure
			( const std::string& failure, 
			  unsigned long line, 
			  const char* file );

		/**	\brief Failure message accessor. */
		std::string Failure
			() const;

		/**	\brief Failure line accessor. */
		unsigned long Line
			() const;

		/**	\brief Failure file accessor. */
		std::string File
			() const;
	};
}

#endif // AERYN_TEST_FAILURE_HPP
