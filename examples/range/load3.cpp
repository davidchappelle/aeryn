
#include "load3.hpp"
#include <algorithm>
#include <cstdlib>

namespace Range
{
	namespace
	{
		class RangeGen
		{
		private:
			VectorOfInt::value_type current_;
			bool inc_;

		public:
			RangeGen( VectorOfInt::value_type begin, bool inc )
				: current_( begin ), inc_( inc )
			{
			}

			VectorOfInt::value_type operator()()
			{
				VectorOfInt::value_type result = current_;

				if ( inc_ )
				{
					++current_;
				}
				else
				{
					--current_;
				}
				
				return result;
			}
		};
	}
	
	VectorOfInt Load3( int begin, int end )
	{
		VectorOfInt result;
		RangeGen rangeGen( begin, begin < end );
		std::generate_n( std::back_inserter( result ), std::abs( end - begin ) + 1, rangeGen );	
		return result;
	}
}
