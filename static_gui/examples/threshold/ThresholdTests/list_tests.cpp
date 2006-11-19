
#include "list_tests.hpp"
#include <threshold/list.hpp>
#include <aeryn/is_true.hpp>

namespace Threshold
{
	namespace Tests
	{
		typedef List< int > ListOfInt;
		
		void ListTests::EmptyTest()
		{
			ListOfInt list;
			IS_TRUE( list.IsEmpty() );
		}
	}
}
