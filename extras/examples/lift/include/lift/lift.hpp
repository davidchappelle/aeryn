
#ifndef LIFT_LIFT_H
#define LIFT_LIFT_H

#include <lift/ilift.hpp>

namespace Lift
{
	class Lift : public ILift
	{
	private:
		const unsigned int floorCount_;

	public:
		explicit Lift( unsigned int floorCount );	
	};
}

#endif // LIFT_LIFT_H
