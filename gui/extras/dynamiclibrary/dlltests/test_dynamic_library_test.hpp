
#ifndef AERYN_DYNAMIC_LIBRARY_TEST_DYNAMIC_LIBRARY_TEST_H
#define AERYN_DYNAMIC_LIBRARY_TEST_DYNAMIC_LIBRARY_TEST_H

#include <string>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		class TestDynamicLibraryTest
		{
		public:
			static void LoadLibraryTest
				( const std::string& path );

			static void TestCountTest
				( const std::string& path );

			static void RunAllTestsTest
				( const std::string& path );
		};
	}
}

#endif // AERYN_DYNAMIC_LIBRARY_TEST_DYNAMIC_LIBRARY_TEST_H
