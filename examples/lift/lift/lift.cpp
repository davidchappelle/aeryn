
#include <lift/lift.hpp>
#include <lift/invalid_floor.hpp>

namespace Lift
{
	Lift::Lift( unsigned int floorCount )
		: ILift(),
		  floorCount_( floorCount ),
		  currentFloor_( 0 )
	{
	}

	int Lift::CurrentFloor() const
	{
		return currentFloor_;
	}

	void Lift::Summon( unsigned int floor )
	{
		if ( floor > floorCount_ )
		{
			throw InvalidFloor( floor );
		}		
			
		currentFloor_ = floor;
	}
}
