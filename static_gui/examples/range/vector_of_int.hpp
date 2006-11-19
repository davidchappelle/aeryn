
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

#ifndef RANGE_VECTOR_OF_INT_HPP
#define RANGE_VECTOR_OF_INT_HPP

#include <aeryn/details/is_streamable.hpp>
#include <vector>

namespace Range
{
	typedef std::vector< int > VectorOfInt;
}

namespace Aeryn
{
	namespace Williams
	{
		template<>
		struct IsStreamable< Range::VectorOfInt >
		{
			static FalseType testStreamable
				( const StreamableResult& );

			static TrueType testStreamable
				(...);

			static const bool result =	true;
		};
	}
}	

std::ostream& operator<<( std::ostream& out, const Range::VectorOfInt& range );

#endif // RANGE_VECTOR_OF_INT_HPP