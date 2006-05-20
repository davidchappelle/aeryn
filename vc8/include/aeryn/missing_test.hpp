
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

/** \file missing_test.hpp
 *  \brief Definition of MISSING_TEST test condition macro, implementation function declaration
 *	and declaration of TestMissing exception.
 */	

#ifndef AERYN_MISSING_TEST_HPP
#define AERYN_MISSING_TEST_HPP

#include <string>

/**	\brief MISSING_TEST test condition macro.
 *
 *	<b>Failure condition:</b>	The MISSING_TEST test condition always throws. It is intended to be used 
 *	to indicate that a test needs to be written.
 *
 *	<b>Failure message:</b>	The string literal contained within msg. 
 *
 *	<b>Example:</b><code> MISSING_TEST( "Test needs to be written" )</code>
 *
 */
#define MISSING_TEST( msg ) ::Aeryn::MissingTest( msg, __LINE__, __FILE__ )

namespace Aeryn
{
	/**	\brief Test missing exception.
	 *
	 *	Thrown but MissingTest function.
	 */
	class TestMissing
	{
	private:
		/**	\brief Missing test description. */
		std::string		description_;
		
		/**	\brief The line where the missing test should be. */
		unsigned long	line_;

		/**	\brief The file in which the missing test should be. */
		const char*	file_;

	public:
		/**	\brief Constructor.
		 *
		 *	\param description A description of the missing test.
		 *	\param line The line where the missing test should be.
		 *	\param file The file in which the missing test should be.
		 */
		TestMissing
			( const std::string& description, 
			  unsigned long line, 
			  const char* file );

		/**	\brief Test description accessor. */
		std::string Description
			() const;

		/**	\brief Test line accessor. */
		unsigned long Line
			() const;

		/**	\brief Test file accessor. */
		std::string File
			() const;
	};
	
	
	/**	\brief Reports that a test is missing by throwing TestMissing.
	 *
	 *	\param msg A message to indicate the failure.
	 *	\param line The line the failure occurred on.
	 *	\param file The file the failure occurred in.
	 *	\throws TestMissing Always throws.
	 */
	void MissingTest
		(	const char* msg, 
			unsigned long line, 
			const char* file );
}

#endif // AERYN_MISSING_TEST_HPP
