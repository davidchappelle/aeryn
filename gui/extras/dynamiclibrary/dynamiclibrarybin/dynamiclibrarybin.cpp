
#include <aeryn/extras/dynamic_library_test_runner.hpp>
#include "../../../tests/add_tests.hpp"

namespace Aeryn
{
	namespace DynamicLibrary
	{
		void AddDynamicLibraryTests( TestRunner& testRunner )
		{
			AddTests( testRunner );
		}
	}
}

