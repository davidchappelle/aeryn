
#ifndef LIFT_EXCEPTION_H
#define LIFT_EXCEPTION_H

#include <stdexcept>

namespace Lift
{
	class Exception : public std::runtime_error
	{
	public:
		Exception( const std::string& msg );
	};
}


#endif // LIFT_EXCEPTION_H
