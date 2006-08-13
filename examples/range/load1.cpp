
#include "load1.hpp"

namespace Range
{
	VectorOfInt Load1( int begin, int end )
	{
		VectorOfInt result;
		for( int i = begin; i != end; ++i )
		{
			result.push_back( i );
		}
		return result;
	}
}
