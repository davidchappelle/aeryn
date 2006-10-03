
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
