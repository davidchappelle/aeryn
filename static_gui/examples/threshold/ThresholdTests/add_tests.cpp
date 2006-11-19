
#include "add_tests.hpp"
#include "list_tests.hpp"

#include <aeryn/test_case.hpp>
#include <aeryn/use_name.hpp>

namespace Threshold
{
	namespace Tests
	{
		namespace
		{
			using namespace Aeryn;
			
			TestCase listTests[] = 
			{ 
				TestCase(USE_NAME(ListTests::EmptyTest )),
				TestCase() 
			};
		}
	
		void AddTests( Aeryn::TestRunner& testRunner )
		{
			testRunner.Add( USE_NAME( listTests ) );
		}
	}
}
