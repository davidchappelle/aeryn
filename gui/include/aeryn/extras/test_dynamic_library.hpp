
#ifndef AERYN_DYNAMIC_LIBRARY_TEST_DYNAMIC_LIBRARY_H
#define AERYN_DYNAMIC_LIBRARY_TEST_DYNAMIC_LIBRARY_H

#include <aeryn/extras/dynamic_library_loader.hpp>
#include <aeryn/exception.hpp>

namespace Aeryn
{
	class IReport;
	
	namespace DynamicLibrary
	{
		class BadDynamicLibraryFunction : public Exception
		{
		private:
			static std::string MakeMessage( DWORD error )
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

		public:
			BadDynamicLibraryFunction
				( DWORD error )
				: Exception( MakeMessage( error ) )
			{
			}
		};
		
		class TestDynamicLibrary : public DynamicLibraryLoader
		{
		public:
			TestDynamicLibrary
				( const std::string path );

			unsigned long TestCount
				() const;

			int RunAllTests
				( IReport& report );
		};
	}
}

#endif // AERYN_DYNAMIC_LIBRARY_TEST_DYNAMIC_LIBRARY_H
