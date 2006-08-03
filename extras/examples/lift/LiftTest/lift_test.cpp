
#include "lift_test.hpp"
#include <lift/lift.hpp>
#include <memory>

namespace LiftTests
{
	void LiftTest::BasicTest()
	{
		std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );


	}
}
