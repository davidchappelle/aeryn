
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

/** \file is_not_equal.cpp
 *  \brief IsNotEqual implementation.
 */	

#include <aeryn/is_not_equal.hpp>
#include <cstring>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	void IsNotEqual
	( 
		const char* lhs, 
		const char* rhs,
		const char* lhscode, 
		const char* rhscode,
		unsigned long line, 
		const char* file 
	)
	{
		if ( 0 == std::strcmp( lhs, rhs) )
		{
			using namespace details;

#ifdef NO_OUTPUT_OPERATOR_DETECTION
			const bool isStreamable = false;
#else 
			const bool isStreamable = true;
#endif		
			throw TestFailure( Print< isStreamable, IsNotEqualFunc >::Out< const char*, const char* >
				( lhs, rhs, lhscode, rhscode ), line, file );
		}
	}

	//////////////////////////////////////////////////////////////////////////	
}
