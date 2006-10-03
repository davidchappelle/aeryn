
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

#include "load1.hpp"

namespace Range
{
	namespace
	{
		inline void insert( VectorOfInt& cont, int value )
		{
			cont.push_back( value );
		}
	}
	
	VectorOfInt Load1( int first, int last )
	{
		VectorOfInt result;
	
		const int direction = last < first ? -1 : 1;

		for( int i = first; i != last; i+= direction )
		{
			insert( result, i );
		}
		insert( result, i );

		return result;
	}
}
