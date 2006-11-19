
#include <lift/exception.hpp>

namespace Lift
{
	Exception::Exception( const std::string& msg )
		: runtime_error( msg )
	{
	}
}
