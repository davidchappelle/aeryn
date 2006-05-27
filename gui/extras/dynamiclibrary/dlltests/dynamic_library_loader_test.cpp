
#include "dynamic_library_loader_test.hpp"
#include <aeryn/extras/dynamic_library_loader.hpp>
#include <aeryn/exception.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/is_true.hpp>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		namespace
		{
#ifdef _DEBUG
			const std::string dllName = "dynamiclibrarybin_debug.dll";
#else
			const std::string dllName = "dynamiclibrarybin.dll";
#endif
			//////////////////////////////////////////////////////////////////////////
			std::string DllPath( const std::string& path )
			{
				return path + dllName;
			}

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
