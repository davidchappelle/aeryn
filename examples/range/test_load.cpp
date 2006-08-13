
#include "test_load.hpp"
#include <aeryn/is_equal.hpp>
#include <algorithm>

namespace Range
{
	namespace
	{
		const int inc[] = {0,1,2,3,4,5,6,7,8,9,10};	
		const int dec[] = {10,9,8,7,6,5,4,3,2,1,0};

		const VectorOfInt goingUp( inc, inc + sizeof( inc ) / sizeof( VectorOfInt::value_type ) );
		const VectorOfInt goingDown( dec, dec + sizeof( dec ) / sizeof( VectorOfInt::value_type ) );

		inline std::ostream& operator<<( std::ostream& out, const VectorOfInt& range )
		{
			std::copy(	range.begin(), 
						range.end(), 
						std::ostream_iterator< VectorOfInt::value_type >( out, "\n" ) );
			return out;
		}	
	}

	void TestLoad( FuncPtr load )
	{
		VectorOfInt vecToTest = load( 0, 10 );
		IS_EQUAL( goingUp, vecToTest );

		vecToTest = load( 10, 0 );
		IS_EQUAL( goingDown, vecToTest );
	}
}
