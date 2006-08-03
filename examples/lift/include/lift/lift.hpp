
#ifndef LIFT_LIFT_H
#define LIFT_LIFT_H

#include <lift/ilift.hpp>

namespace Lift
{
	class Lift : public ILift
	{
	private:
		const unsigned int floorCount_;
		unsigned int currentFloor_;

	public:
		explicit Lift( unsigned int floorCount );

		virtual int CurrentFloor() const;
		virtual void Summon( unsigned int floor );
	};
}

#endif // LIFT_LIFT_H
