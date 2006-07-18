
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

/** \file context_object_test.hpp
 *  \brief Context object test declarations.
 */	

#ifndef AERYN_CONTEXT_OBJECT_TESTS_HPP
#define AERYN_CONTEXT_OBJECT_TESTS_HPP

namespace Aeryn
{
	/**	\brief A constant to use in the tests. */
	const int lifeTheUniverseAndEverything = 42;

	/**	\brief A test fixture function that takes a context object. 
	 *
	 *	Uses IsEqual to compare lifeTheUniverseAndEverything with a.
	 *	
	 *	\param a A context object.
	 */
	void ContextObjectFunc
		( int a );

	/**	\brief A fixture class that takes a context object. */
	class ContextObjectClass
	{
	private:
		/**	\brief A copy of the context object. */
		const int a_;

	public:
		/**	\brief Constructor.
		 *
		 *	\param a A context object. */
		ContextObjectClass
			( int a );

		/**	\brief Uses IsEqual to compare lifeTheUniverseAndEverything with a_. */
		void Run
			();
	};

}

#endif // AERYN_CONTEXT_OBJECT_TESTS_HPP
