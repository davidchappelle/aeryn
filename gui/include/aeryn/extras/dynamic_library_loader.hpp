
#ifndef AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_LOADER_H
#define AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_LOADER_H

#include <aeryn/details/noncopyable.hpp>
#include <windows.h>
#include <string>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		class DynamicLibraryLoader : private Utils::Noncopyable
		{
		private:
			HINSTANCE handle_;

		protected:
			const HINSTANCE& LibraryHandle
				() const;

		public:
			DynamicLibraryLoader
				( const std::string path );

			~DynamicLibraryLoader
				();
		};
	}
}

#endif // AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_LOADER_H
