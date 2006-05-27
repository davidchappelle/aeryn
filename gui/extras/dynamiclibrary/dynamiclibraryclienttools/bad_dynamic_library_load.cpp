
#include <aeryn/extras/bad_dynamic_library_load.hpp>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		std::string BadDynamicLibraryLoad::MakeMessage( DWORD error )
		{
			std::string result;

			LPVOID lpMsgBuf;
			if (FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | 
								FORMAT_MESSAGE_FROM_SYSTEM | 
								FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL,
								error,
								MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
								(LPTSTR) &lpMsgBuf,
								0,
								NULL ))
			{
				result = (LPCTSTR)lpMsgBuf;

				// Free the buffer.
				LocalFree( lpMsgBuf );
			}

			return result;
		}

		//////////////////////////////////////////////////////////////////////////
		BadDynamicLibraryLoad::BadDynamicLibraryLoad( DWORD error )
			: Exception( MakeMessage( error ) )
		{
		}

	}
}