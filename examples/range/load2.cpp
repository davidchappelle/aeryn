
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
	
	VectorOfInt Load2( int begin, int end )
	{
		VectorOfInt result;

		int i = begin;
		while( i != end )
		{
			insert( result, i );

			if ( begin < end )
				++i;
			else
				--i;
		}
		insert( result, i );
		
		return result;
	}
}
