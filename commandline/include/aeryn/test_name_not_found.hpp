
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2006 Paul Grenyer
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

/** \file test_name_not_found.hpp
 *  \brief TestNameNotFound declaration.
 */	

#ifndef AERYN_TEST_NAME_NOT_FOUND_HPP
#define AERYN_TEST_NAME_NOT_FOUND_HPP

#include <aeryn/exception.hpp>

namespace Aeryn
{
	/**	\brief Thrown when a test cannot be found when searched for by name. */
	class TestNameNotFound : public Exception
	{
	public:
		/** \brief Constructor
		 *
		 *	\brief name The name of the test that can't be found.
		 */
		explicit TestNameNotFound
			( const std::string& name );
	};
}

#endif // AERYN_TEST_NAME_NOT_FOUND_HPP
