
#include "load2.hpp"

namespace Range
{
	namespace
	{
		inline void insert( VectorOfInt& cont, int value )
		{
			cont.push_back( value );
		}
	}
	
	VectorOfInt Load2( int first, int last )
	{
		VectorOfInt result;

		int i = first;
		while( i != last )
		{
			insert( result, i );

			if ( first < last )
				++i;
			else
				--i;
		}
		insert( result, i );
		
		return result;
	}
}
