
#include "add_tests.hpp"
#include "lift_test.hpp"

#include <aeryn/test_case.hpp>
#include <aeryn/use_name.hpp>

namespace LiftTests
{
	namespace
	{
		using namespace Aeryn;
		
		TestCase liftTest[] = 
		{ 
			TestCase( USE_NAME( LiftTest::BasicTest ) ),
			TestCase() 
		};
	}
	
	void AddTests( Aeryn::TestRunner& testRunner )
	{
		testRunner.Add( USE_NAME( liftTest ) );
	}
}

