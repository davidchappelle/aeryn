
#ifndef LIFT_INVALID_FLOOR_H
#define LIFT_INVALID_FLOOR_H

#include <lift/exception.hpp>

namespace Lift
{
	class InvalidFloor : public Exception
	{
	public:
		InvalidFloor( unsigned int floor );
	};
}


#endif // LIFT_INVALID_FLOOR_H
