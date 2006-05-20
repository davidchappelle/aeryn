
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

/** \file context_object_test.cpp
 *  \brief Context object test definitions.
 */	

#include "context_object_test.hpp"
#include <aeryn/is_equal.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	void ContextObjectFunc
	( 
		int a 
	)
	{
		IS_EQUAL( lifeTheUniverseAndEverything, a );
	}

	//////////////////////////////////////////////////////////////////////////
	ContextObjectClass::ContextObjectClass
	( 
		int a 
	) : a_( a )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void ContextObjectClass::Run()
	{
		IS_EQUAL( lifeTheUniverseAndEverything, a_ );
	}	
}
