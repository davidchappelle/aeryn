
#include <lift/imonitor.hpp>
#include <lift/invalid_floor.hpp>
#include <lift/lift.hpp>
#include <algorithm>

namespace Lift
{
	namespace
	{
		class UpdateMonitorsFunc
		{
		private:
			const ILift* lift_;

		public:
			explicit UpdateMonitorsFunc( const ILift* lift )
				: lift_( lift )
			{
			}

			void operator()( IMonitor* monitor )
			{
				monitor->Update( lift_ );
			}
		};
	}
	
	Lift::Lift( unsigned int floorCount )
		: ILift(),
		  floorCount_( floorCount ),
		  currentFloor_( 0 ),
		  monitors_()
	{
	}

	unsigned int Lift::CurrentFloor() const
	{
		return currentFloor_;
	}

	void Lift::Summon( unsigned int floor )
	{
		if ( floor > floorCount_ )
		{
			throw InvalidFloor( floor );
		}

		const bool goingUp = CurrentFloor() < floor ? true : false;
		
		while( currentFloor_ != floor )
		{
			NotifyMonitors();

			if ( goingUp )
			{
				++currentFloor_;
			}
			else
			{
				--currentFloor_;
			}
		}

		NotifyMonitors();
	}

	void Lift::AddMonitor( IMonitor* monitor )
	{
		monitors_.push_back( monitor );
	}

	void Lift::NotifyMonitors() const
	{
		UpdateMonitorsFunc updateMonitorsFunc( this );
		std::for_each(	monitors_.begin(),
						monitors_.end(),
						updateMonitorsFunc );
	}
}

