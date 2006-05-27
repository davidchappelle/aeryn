
#include <aeryn/extras/dynamic_library_test_runner.hpp>
#include <aeryn/test_runner.hpp>

DYNAMIC_LIBRARY_API unsigned long DynamicLibraryTestCount()
{
	using namespace Aeryn;
	DynamicLibrary::DynamicLibraryTestRunner testRunner;
	DynamicLibrary::AddDynamicLibraryTests( testRunner );
	return testRunner.TestCount();
}

DYNAMIC_LIBRARY_API int DynamicLibraryRunAllTests
	( Aeryn::IReport& report )
{
	using namespace Aeryn;
	DynamicLibrary::DynamicLibraryTestRunner testRunner;
	DynamicLibrary::AddDynamicLibraryTests( testRunner );
	return testRunner.Run( report );
}

namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		DynamicLibraryTestRunner::DynamicLibraryTestRunner
		( 
			const ReportFactory& reportFactory /* = ReportFactory() */
		)
		: TestRunner( reportFactory )
		{
		}

		//////////////////////////////////////////////////////////////////////////
		unsigned long DynamicLibraryTestRunner::TestCount
			() const
		{
			return TestRunner::TestCount();
		}
		

		//////////////////////////////////////////////////////////////////////////		
	}
}
