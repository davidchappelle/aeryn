
#include "test_dynamic_library_test.hpp"
#include "dll_path.h"
#include <aeryn/extras/test_dynamic_library.hpp>
#include <aeryn/exception.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/minimal_report.hpp>
#include <aeryn/is_true.hpp>
#include <aeryn/is_equal.hpp>
#include <sstream>

namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		void TestDynamicLibraryTest::LoadLibraryTest
		(
			const std::string& path
		)
		{
			try
			{
				TestDynamicLibrary testDynamicLibrary( DllPath( path ) );				
			}
			catch( const Exception& e )
			{
				FAILED( e.What().c_str() );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		void TestDynamicLibraryTest::TestCountTest
		( 
			const std::string& path 
		)
		{
			try
			{
				TestDynamicLibrary testDynamicLibrary( DllPath( path ) );
				IS_EQUAL( 43, testDynamicLibrary.TestCount() );
			}
			catch( const Exception& e )
			{
				FAILED( e.What().c_str() );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		void TestDynamicLibraryTest::RunAllTestsTest
		( 
			const std::string& path 
		)
		{
			const std::string expectedResult =
				"\n"
				"Aeryn 2.1.2 (c) Paul Grenyer 2005-2006\n"
				"http://www.aeryn.co.uk/\n"
				"------------------------------------------------------------\n"
				"\n"
				"Ran 43 tests, 43 Passed, 0 Failed.\n"
				"\n";
			
			try
			{
				std::stringstream str;
				MinimalReport report( str );
				TestDynamicLibrary testDynamicLibrary( DllPath( path ) );
				IS_TRUE( 0 == testDynamicLibrary.RunAllTests( report ) );
				const std::string result = str.str();
				IS_EQUAL( expectedResult, result );			

			}
			catch( const Exception& e )
			{
				FAILED( e.What().c_str() );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		
	}
}

