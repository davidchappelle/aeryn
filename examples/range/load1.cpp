
#include "load1.hpp"

namespace Range
{
	VectorOfInt Load1( int first, int last )
	{
		VectorOfInt result;
		if ( first < last )
		{
			for( int i = first; i != last ; ++i )
			{
				result.push_back( i );
			}
		}
		else
		{
			for( int i = first; i != last - 1; --i )
			{
				result.push_back( i );
			}
		}
		return result;
	}
}
