
#include "test_load.hpp"
#include <aeryn/is_equal.hpp>

namespace Range
{
	namespace
	{
		const int inc[] = {0,1,2,3,4,5,6,7,8,9,10};
		const int dec[] = {10,9,8,7,6,5,4,3,2,1,0};

		const VectorOfInt goingUp( inc, inc + sizeof( inc ) / sizeof( int ) );
		const VectorOfInt goingDown( dec, dec + sizeof( dec ) / sizeof( int ) );

		const int negativeInc[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
		const int negativeDec[] = {5,4,3,2,1,0,-1,-2,-3,-4,-5};

		const VectorOfInt negativeGoingUp( negativeInc, negativeInc + sizeof( negativeInc ) / sizeof( int ) );
		const VectorOfInt negativeGoingDown( negativeDec, negativeDec + sizeof( negativeDec ) / sizeof( int ) );
			
	}	

	void TestLoadInc( FuncPtr load )
	{
		VectorOfInt vecToTest = load( 0, 10 );
		IS_EQUAL( goingUp, vecToTest );
	}

	void TestLoadDec( FuncPtr load )
	{
		VectorOfInt vecToTest = load( 10, 0 );
		IS_EQUAL( goingDown, vecToTest );
	}

	void TestLoadNegInc( FuncPtr load )
	{
		VectorOfInt vecToTest = load( -5, 5 );
		IS_EQUAL( negativeGoingUp, vecToTest );
	}

	void TestLoadNegDec( FuncPtr load )
	{
		VectorOfInt vecToTest = load( 5, -5 );
		IS_EQUAL( negativeGoingDown, vecToTest );
	}
}
