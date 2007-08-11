
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

/** \file test_case.cpp
 *  \brief TestCase implementation.
 */	

#include <aeryn/test_case.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		/**	\brief Default test case name. */
		const char* defaultTestName = "";
	}
	
	//////////////////////////////////////////////////////////////////////////
	TestCase::TestCase
		()
	: name_(),
	  func_(),
	  isNull_( true )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	TestCase::TestCase
	( 
		FunctionPtr func 
	) : name_( defaultTestName ),
		func_( func ),
		isNull_( false )
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	TestCase::TestCase
	( 
		const std::string& name, 
		FunctionPtr func
	) : name_( name ),
		func_( func ),
		isNull_( false )
	{
/*		if ( func.has_context() )
		{			
			std::stringstream str;
			str << name << "( " << func.context_string() << " ) ";
			name_ = str.str();
		}		*/
	}

	//////////////////////////////////////////////////////////////////////////
	const std::string TestCase::Name
		() const
	{
		return name_;
	}	

	//////////////////////////////////////////////////////////////////////////
	void TestCase::Run
		() const
	{
		func_();
	}

	//////////////////////////////////////////////////////////////////////////
	bool TestCase::IsNull
		() const
	{
		return isNull_;
	}

	//////////////////////////////////////////////////////////////////////////	
}

