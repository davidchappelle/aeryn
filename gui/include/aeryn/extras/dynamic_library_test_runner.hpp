
#ifndef AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_TEST_RUNNER_H
#define AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_TEST_RUNNER_H

#include <aeryn/test_runner.hpp>
#include <aeryn/ireport.hpp>

#ifdef DYNAMIC_LIBRARY_EXPORTS
	#define DYNAMIC_LIBRARY_API __declspec(dllexport)
#else
	#define DYNAMIC_LIBRARY_API __declspec(dllimport)
#endif

DYNAMIC_LIBRARY_API unsigned long DynamicLibraryTestCount();

DYNAMIC_LIBRARY_API int DynamicLibraryRunAllTests( Aeryn::IReport& report );

namespace Aeryn
{
	namespace DynamicLibrary
	{
		class DynamicLibraryTestRunner : public TestRunner
		{
		public:
			/**	\brief Default constructor. 
			*
			*	\param reportFactory Factory used to create reports. Default = ReportFactory.
			*/
			explicit DynamicLibraryTestRunner
				( const ReportFactory& reportFactory = ReportFactory() );

			unsigned long TestCount
				() const;
		};
		
		
		void AddDynamicLibraryTests
			( TestRunner& tests );		
	}
}

#endif // AERYN_DYNAMIC_LIBRARY_DYNAMIC_LIBRARY_TEST_RUNNER_H