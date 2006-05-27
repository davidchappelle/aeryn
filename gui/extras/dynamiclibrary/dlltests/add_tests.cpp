
#include "add_tests.hpp"
#include "dynamic_library_loader_test.hpp"
#include "test_dynamic_library_test.hpp"
#include <aeryn/test_case.hpp>
#include <aeryn/use_name.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		namespace
		{
			//////////////////////////////////////////////////////////////////////////
			const std::string RemoveAppName
				( const std::string& appPath )
			{
				const std::string::size_type pos = appPath.rfind( "\\" );
				if ( pos != std::string::npos )
				{
					return appPath.substr( 0, pos + 1 );
				}
				else
				{
					return appPath;
				}
			}
		}
		
		//////////////////////////////////////////////////////////////////////////
		void AddTests
		( 
			TestRunner& testRunner,
			const std::string& appPath
		)
		{
			const std::string path = RemoveAppName( appPath );
			
			TestCase dynamicLibraryLoaderTests[] = 
				{	TestCase(	"Load Library Test", 
								FunctionPtr( DynamicLibraryLoaderTest::LoadLibraryTest, path ) ),
					TestCase(	"Load Library Fail Test", 
								FunctionPtr( DynamicLibraryLoaderTest::LoadLibraryFailTest, path ) ),
					TestCase() };	

			TestCase testDynamicLibraryTests[] = 
				{	TestCase(	"Load Library Test", 
								FunctionPtr( TestDynamicLibraryTest::LoadLibraryTest, path ) ),
					TestCase(	"Test Count Test", 
								FunctionPtr( TestDynamicLibraryTest::TestCountTest, path ) ),
					TestCase(	"Run All Tests Test", 
								FunctionPtr( TestDynamicLibraryTest::RunAllTestsTest, path ) ),
					TestCase() };			
			
			
			testRunner.Add( USE_NAME( dynamicLibraryLoaderTests ) );
			testRunner.Add( USE_NAME( testDynamicLibraryTests ) );
		}

		//////////////////////////////////////////////////////////////////////////
		
	}
}
