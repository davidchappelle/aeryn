
#ifndef RANGE_TEST_LOAD_HPP
#define RANGE_TEST_LOAD_HPP

#include "vector_of_int.hpp"

namespace Range
{
	typedef VectorOfInt (*FuncPtr)(int,int);

	void TestLoadInc( FuncPtr load );
	void TestLoadDec( FuncPtr load );
	void TestLoadNegInc( FuncPtr load );
	void TestLoadNegDec( FuncPtr load );
}

#endif // RANGE_TEST_LOAD_HPP