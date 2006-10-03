
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
