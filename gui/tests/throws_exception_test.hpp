
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

/** \file throws_exception_test.hpp
 *  \brief Declaration of THROWS_EXCEPTION and DOES_NOT_THROW_EXCEPTION tests.
 */	

#ifndef AERYN_THROWS_EXCEPTION_TEST_HPP
#define AERYN_THROWS_EXCEPTION_TEST_HPP

namespace Aeryn
{
	/**	\brief Test for correct exception being thrown. */
	void ThrowsExceptionTest
		();

	/**	\brief Test for exception not being thrown. */
	void ThrowsExceptionFailTest
		();

	/**	\brief Test for wrong type of exception being thrown. */
	void ThrowsExceptionWrongExceptionTest
		();
	
	/**	\brief Test for no exception being thrown. */
	void DoesNotThrowExceptionTest
		();

	/**	\brief Tests for exception being thrown. */
	void DoesNotThrowExceptionFailTest
		();	
}

#endif // AERYN_THROWS_EXCEPTION_TEST_HPP
