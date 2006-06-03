
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

/** \file test_case.hpp
 *  \brief TestCase declaration.
 */	

#ifndef AERYN_TEST_CASE_HPP
#define AERYN_TEST_CASE_HPP

#include <aeryn/details/function_ptr.hpp>
#include <aeryn/details/incarnate.hpp>
#include <string>

namespace Aeryn
{
	/**	\brief A wrapper for a test fixture which enables it to be given a name and run. */
	class TestCase
	{
	private:
		/**	\brief The name given to the test case. */
		std::string name_;

		/**	\brief A pointer to the function that is called when the test case is run. */
		FunctionPtr func_;

		/**	\brief Indicates if the test fixture is a null terminator. */
		bool		isNull_;

	public:
		/**	\brief Used to create a null terminator. */
		explicit TestCase
			();

		/**	\brief Used to create a default named test TestCase. 
		 *
		 *	\param func A pointer to the function that is called when the test case is run.
		 */
		explicit TestCase
			( FunctionPtr func );

		/**	\brief Used to create a named test TestCase. 
		 *
		 *	\param name A name used to identify the test case.
		 *	\param func A pointer to the function that is called when the test case is run.
		 */
		explicit TestCase
			( const std::string& name, 
			  FunctionPtr func );		

		/**	\brief Test case name accessor. */
		const std::string Name
			() const;

		/**	\brief Calls the test fixture contained in the test case. */
		void Run
			() const;	

		/**	\brief Indicates if the test case is a null terminator. */
		bool IsNull
			() const;
	};	
}

#endif // AERYN_TEST_CASE_HPP
