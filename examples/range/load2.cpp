
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

#include "load2.hpp"
#include <algorithm>
#include <cstdlib>

namespace Range
{
	namespace
	{
		class RangeGen
		{
		private:
			int current_;
			int step_;

		public:
			RangeGen( int first, int last )
				: current_( first ), step_( first < last ? 1 : -1 )
			{
			}

			int operator()()
			{
				int result = current_;
				current_ += step_;				
				return result;
			}
		};
	}

	VectorOfInt Load2( int first, int last )
	{
		VectorOfInt result;
		RangeGen rangeGen( first, last );
		std::generate_n( std::back_inserter( result ), std::abs( last - first ) + 1, rangeGen );	
		return result;
	}
}
