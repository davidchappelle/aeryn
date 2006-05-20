
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2005 Paul Grenyer
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *  
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/** \file test_set_runner.cpp
 *  \brief TestSetRunner definition.
 */	

#include "test_set_runner.h"
#include <aeryn/test_failure.hpp>
#include <aeryn/missing_test.hpp>
#include <cassert>


namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace 
	{
		/**	\brief Aeryn copyright message. */
		const std::string header =	"\n"
									"Aeryn 2.1.2 (c) Paul Grenyer 2005-2006\n"
									"http://www.aeryn.co.uk/\n";
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetRunner::TestSetRunner
	( 
		const TestSetCont& testSets, 
		IReport& report 
	)
	: testSets_( testSets ),
	  report_( report )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	int TestSetRunner::Run()
	{
		const unsigned long testCout	= static_cast<unsigned long>( testSets_.TestCount() );
		unsigned long failureCount		= 0;
		unsigned long missingCount		= 0;
		report_.BeginTesting( header, testCout );

		TestSetCont::ConstItr currentTestSet	= testSets_.Begin();
		TestSetCont::ConstItr endTestSet		= testSets_.End();

		for( ; currentTestSet != endTestSet; ++currentTestSet )
		{
			RunTestSet( failureCount, missingCount, *currentTestSet, report_ );			
		}

		report_.EndTesting( testCout, failureCount, missingCount );

		return failureCount != 0 ? -1 : 0;
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetRunner::RunTestSet
	( 
		unsigned long& failureCount,
		unsigned long& missingCount,
		const TestSet& testSet,
		IReport& report 
	) const
	{
		report.BeginTestSet( testSet.second );

		TestCaseCont::const_iterator current	= testSet.first.begin();
		TestCaseCont::const_iterator end		= testSet.first.end();

		for( ; current != end; ++current )
		{
			RunTest( failureCount, missingCount, *current, report );
		}

		report.EndTestSet( testSet.second );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetRunner::RunTest
	( 
		unsigned long& failureCount,
		unsigned long& missingCount,
		const TestCase& test,
		IReport& report 
	) const
	{
		report.BeginTest( test.Name() );

		switch( RunTest( test, report ) )
		{
		case FAILED:
			++failureCount;
			break;

		case PASSED:
			break;

		case MISSING:
			++missingCount;
			break;

		default:
			assert( !"Unknown result type." );
		};				

		report.EndTest( test.Name() );
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetRunner::Result TestSetRunner::RunTest
	(
		const TestCase& test,
		IReport& report 
	) const
	{
		Result result = FAILED;

		try
		{
			test.Run();
			report.Pass( test.Name() );
			result = PASSED;
		}
		catch( const TestFailure& e )
		{
			report.Failure( test.Name(), e );
		}
		catch( const TestMissing& e )
		{
			report.MissingTest( test.Name(), e );
			result = MISSING;
		}
		catch( const std::exception& e )
		{
			report.Error( test.Name(), e.what() );
		}
		catch( ... )
		{
			report.Error( test.Name(), "!!! Unknown Error !!!" );
		}	

		return result;
	}	
}
