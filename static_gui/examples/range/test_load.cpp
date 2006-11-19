
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2006 Paul Grenyer
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "test_load.hpp"
#include <aeryn/is_equal.hpp>

namespace Range
{
	namespace
	{
		const int inc[] = {0,1,2,3,4,5,6,7,8,9,10};
		const int dec[] = {10,9,8,7,6,5,4,3,2,1,0};

		const VectorOfInt goingUp( inc, inc + sizeof( inc ) / sizeof( inc[0] ) );
		const VectorOfInt goingDown( dec, dec + sizeof( dec ) / sizeof( dec[0] ) );

		const int negativeInc[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
		const int negativeDec[] = {5,4,3,2,1,0,-1,-2,-3,-4,-5};

		const VectorOfInt negativeGoingUp( negativeInc, negativeInc + sizeof( negativeInc ) / sizeof( negativeInc[0] ) );
		const VectorOfInt negativeGoingDown( negativeDec, negativeDec + sizeof( negativeDec ) / sizeof( negativeDec[0] ) );
			
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
