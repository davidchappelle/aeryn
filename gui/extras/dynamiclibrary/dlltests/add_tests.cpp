
#include "add_tests.hpp"
#include "dynamic_library_loader_test.hpp"
#include <aeryn/test_case.hpp>
#include <aeryn/use_name.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace DynamicLibrary
	{
		TestCase dynamicLibraryLoaderTests[] = {	TestCase( USE_NAME( DynamicLibraryLoaderTest::LoadLibrary ) ),
													TestCase() };
		
		//////////////////////////////////////////////////////////////////////////
		void AddTests
		( 
			TestRunner& testRunner 
		)
		{
			
			
			
			testRunner.Add( USE_NAME( dynamicLibraryLoaderTests ) );
		}

		//////////////////////////////////////////////////////////////////////////
		
	}
}
