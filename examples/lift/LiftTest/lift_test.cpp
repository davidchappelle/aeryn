
#include "lift_test.hpp"
#include <lift/lift.hpp>
#include <lift/invalid_floor.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/throws_exception.hpp>
#include <aeryn/failed.hpp>
#include <sstream>
#include <memory>

namespace LiftTests
{
	void LiftTest::BasicTest()
	{
		std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );
		IS_EQUAL( 0, pLift->CurrentFloor() );
		pLift->Summon( 5 );
		IS_EQUAL( 5, pLift->CurrentFloor() );
	}

	void LiftTest::InvalidFloorTest()
	{
		std::auto_ptr< Lift::ILift > pLift( new Lift::Lift( 10 ) );
		THROWS_EXCEPTION( pLift->Summon( 11 ); , Lift::InvalidFloor );

		try
		{
			pLift->Summon( -1 );
			FAILED( "Failed to throw Lift::InvalidFloor" );
		}
		catch( const Lift::InvalidFloor& e )
		{
			const unsigned int floor = -1;
			std::stringstream expectedMsg;
			expectedMsg << floor << " is an invalid floor";
			IS_EQUAL( expectedMsg.str(), e.what() );
		}
	}
}
