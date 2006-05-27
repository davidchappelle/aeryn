
#ifndef AERYN_DYNAMIC_LIBRARY_DYNAMIC_BAD_DYNAMIC_LIBRARY_LOADER_H
#define AERYN_DYNAMIC_LIBRARY_DYNAMIC_BAD_DYNAMIC_LIBRARY_LOADER_H

#include <aeryn/exception.hpp>
#include <windows.h>
#include <string>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		class BadDynamicLibraryLoad : public Exception
		{
		private:
			static std::string MakeMessage
				( DWORD error );

		public:
			BadDynamicLibraryLoad
				( DWORD error );
		};
	}
}

#endif // AERYN_DYNAMIC_LIBRARY_DYNAMIC_BAD_DYNAMIC_LIBRARY_LOADER_H
