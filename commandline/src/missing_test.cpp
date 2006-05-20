
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

/** \file missing_test.cpp
 *  \brief Implementation of MissingTest and TestMissing exception.
 */	

#include <aeryn/missing_test.hpp>
#include <aeryn/test_failure.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	TestMissing::TestMissing
	( 
		const std::string& description, 
		unsigned long line, 
		const char* file 
	) :	description_( description ), 
		line_(line), 
		file_( file )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	std::string TestMissing::Description
		() const
	{
		return description_;
	}

	//////////////////////////////////////////////////////////////////////////
	unsigned long TestMissing::Line
		() const
	{
		return line_;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string TestMissing::File
		() const
	{
		return file_;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void MissingTest
	( 
		const char* msg, 
		unsigned long line, 
		const char* file  
	)
	{
		throw TestMissing( msg, line, file );
	}
}
