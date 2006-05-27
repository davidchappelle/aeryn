
#include <aeryn/extras/dynamic_library_loader.hpp>
#include <aeryn/extras/bad_dynamic_library_load.hpp>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		DynamicLibraryLoader::DynamicLibraryLoader
		( 
			const std::string path 
		)
		: handle_( 0 )
		{
			handle_ = ::LoadLibrary( path.c_str() );
			if ( !handle_ )
			{
				throw BadDynamicLibraryLoad( ::GetLastError() );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		DynamicLibraryLoader::~DynamicLibraryLoader
			()
		{
			::FreeLibrary( handle_ );
		}

		//////////////////////////////////////////////////////////////////////////
		const HINSTANCE& DynamicLibraryLoader::LibraryHandle
			() const
		{
			return handle_;
		}

		//////////////////////////////////////////////////////////////////////////
		
		
	}
}