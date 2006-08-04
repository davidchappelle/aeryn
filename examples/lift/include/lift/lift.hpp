
#ifndef LIFT_LIFT_H
#define LIFT_LIFT_H

#include <lift/ilift.hpp>
#include <vector>

namespace Lift
{
	class Lift : public ILift
	{
	private:
		typedef std::vector< IMonitor* > IMonitorCont;
		const unsigned int floorCount_;
		unsigned int currentFloor_;
		IMonitorCont monitors_;

	public:
		explicit Lift( unsigned int floorCount );

		virtual unsigned int CurrentFloor() const;
		virtual void Summon( unsigned int floor );
		virtual void AddMonitor( IMonitor* monitor );

	private:
		void NotifyMonitors() const;
	};
}

#endif // LIFT_LIFT_H
