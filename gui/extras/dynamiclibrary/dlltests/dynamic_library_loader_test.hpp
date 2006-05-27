
#ifndef AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_LOADER_TEST_H
#define AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_LOADER_TEST_H

#include <string>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		class DynamicLibraryLoaderTest
		{
		public:
			static void LoadLibraryTest
				( const std::string& path );

			static void LoadLibraryFailTest
				( const std::string& path );
		};
	}
}

#endif // AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_LOADER_TEST_H
