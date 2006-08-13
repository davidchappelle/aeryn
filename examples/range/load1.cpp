
#include "load1.hpp"

namespace Range
{
	VectorOfInt Load1( int begin, int end )
	{
		VectorOfInt result;
		if ( begin < end )
		{
			for( int i = begin; i != end + 1; ++i )
			{
				result.push_back( i );
			}
		}
		else
		{
			for( int i = begin; i != end - 1; --i )
			{
				result.push_back( i );
			}
		}
		return result;
	}
}
