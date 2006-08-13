
#ifndef RANGE_TEST_LOAD_HPP
#define RANGE_TEST_LOAD_HPP

#include "vector_of_int.hpp"

namespace Range
{
	typedef VectorOfInt (*FuncPtr)(int,int);

	void TestLoad( FuncPtr load );
}

#endif // RANGE_TEST_LOAD_HPP