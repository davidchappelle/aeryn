

#ifndef AERYN_DYNAMIC_LIBRARY_ADD_TESTS
#define AERYN_DYNAMIC_LIBRARY_ADD_TESTS

#include <aeryn/test_runner.hpp>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		void AddTests
			( TestRunner& testRunner,
			  const std::string& appPath );
	}
}


#endif // #ifndef AERYN_DYNAMIC_LIBRARY_ADD_TESTS
