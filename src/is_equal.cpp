
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

/** \file is_equal.cpp
 *  \brief IsEqual implementation.
 */	

#include <aeryn/is_equal.hpp>
#include <limits>

namespace Aeryn
{
	void IsEqual
	( 
		const char* lhs, 
		const char* rhs,
		const char* lhscode, 
		const char* rhscode,
		unsigned long line, 
		const char* file 
	)
	{
		if ( 0 != std::strcmp( lhs, rhs) )
		{
			using namespace details;

#ifdef NO_OUTPUT_OPERATOR_DETECTION
			const bool isStreamable = false;
#else 
			const bool isStreamable = true;
#endif			
			throw TestFailure( Print< isStreamable, IsEqualFunc >::Out< const char*, const char* >
				( lhs, rhs, lhscode, rhscode ), line, file );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void IsEqual
	( 
		const double lhs, 
		const double rhs,
		const char* lhscode, 
		const char* rhscode,
		unsigned long line, 
		const char* file 
	)
	{
		const double eps = std::numeric_limits< double >::epsilon();
		
		if ( std::abs( lhs - rhs ) > eps )
		{
			using namespace details;
			throw TestFailure( Print< true, IsEqualFunc >::template Out< double, double >
				( lhs, rhs, lhscode, rhscode ), line, file );
		}
	}

	//////////////////////////////////////////////////////////////////////////	
}
