
#include <lift/invalid_floor.hpp>
#include <sstream>

namespace Lift
{
	namespace
	{
		inline std::string CreateMessage( unsigned int floor )
		{
			std::stringstream msg;
			msg << floor << " is an invalid floor";
			return msg.str();
		}
	}
	
	InvalidFloor::InvalidFloor( unsigned int floor )
		: Exception( CreateMessage( floor ) )
	{
	}
}