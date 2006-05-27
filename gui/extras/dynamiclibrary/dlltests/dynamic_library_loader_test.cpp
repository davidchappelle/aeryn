
#include "dynamic_library_loader_test.hpp"
#include "dll_path.h"
#include <aeryn/extras/dynamic_library_loader.hpp>
#include <aeryn/exception.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/is_true.hpp>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		namespace
		{
			//////////////////////////////////////////////////////////////////////////
			class DynamicLibraryLoaderFake : public DynamicLibraryLoader
			{
			public:
				//////////////////////////////////////////////////////////////////////////
				DynamicLibraryLoaderFake( const std::string& path )
					: DynamicLibraryLoader( path )
				{
				}

				//////////////////////////////////////////////////////////////////////////
				const HINSTANCE& LibraryHandle
					() const
				{
					return DynamicLibraryLoader::LibraryHandle();
				}
			};

		}
		
		//////////////////////////////////////////////////////////////////////////
		void DynamicLibraryLoaderTest::LoadLibraryTest
		( 
			const std::string& path 
		)
		{
			try
			{
				DynamicLibraryLoaderFake dynamicLibraryLoader( DllPath( path ) );
				IS_TRUE( 0 != dynamicLibraryLoader.LibraryHandle() );
			}
			catch( const Exception& e )
			{
				FAILED( e.What().c_str() );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		void DynamicLibraryLoaderTest::LoadLibraryFailTest
		( 
			const std::string& path 
		)
		{
			try
			{
				DynamicLibraryLoaderFake dynamicLibraryLoader( path );
				FAILED( "Loaded unknown library" );
			}
			catch( const Exception& e )
			{
				IS_EQUAL( "The specified module could not be found.\r\n", e.What() );
			}
		}

		//////////////////////////////////////////////////////////////////////////	
		
	}
}
