
#include <aeryn/extras/test_dynamic_library.hpp>


namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		TestDynamicLibrary::TestDynamicLibrary
		( 
			const std::string path 
		) : DynamicLibraryLoader( path )
		{
		}

		//////////////////////////////////////////////////////////////////////////
		unsigned long TestDynamicLibrary::TestCount
			() const
		{
			FARPROC fn = GetProcAddress( LibraryHandle(), "DynamicLibraryTestCount" );
			if ( !fn )
			{
				throw BadDynamicLibraryFunction( GetLastError() );
			}

			return fn();
		}

		//////////////////////////////////////////////////////////////////////////
		int TestDynamicLibrary::RunAllTests
			( IReport& report )
		{
			typedef int (*FN)(IReport&);
			
			FN fn = (FN) GetProcAddress( LibraryHandle(), "DynamicLibraryRunAllTests" );
			if ( !fn )
			{
				throw BadDynamicLibraryFunction( GetLastError() );
			}

			return fn( report );
		}

		//////////////////////////////////////////////////////////////////////////		
		
	}
}
