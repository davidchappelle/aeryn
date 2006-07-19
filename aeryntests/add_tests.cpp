
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

/** \file add_tests.cpp
  *  \brief AddTest definition.
  */	

#include "verbose_report_test.hpp"
#include "minimal_report_test.hpp"
#include "terse_report_test.hpp"
#include "test_failure_test.hpp"
#include "test_func_test.hpp"
#include "throws_exception_test.hpp"
#include "context_object_test.hpp"
#include "simple_date_test.hpp"
#include "test_runner_test.hpp"
#include "command_line_parser_test.hpp"

#include "add_tests.hpp"

#include <aeryn/is_equal.hpp>
#include <aeryn/test_registry.hpp>

#include <iostream>

namespace Aeryn
{	
	/**	\brief Array of report tests. */
	TestCase reportTests[] = 
	{
		TestCase( USE_NAME( MinimalReportTest ) ),
		TestCase( USE_NAME( VerboseReportTest ) ),
		TestCase( USE_NAME( TerseReportTest ) ),		
		TestCase()
	};
	
	/**	\brief Array of TestFailure tests. */
	TestCase testFailureTests[] =
	{
		TestCase( TestFailureTest::BasicAccessor ),
		TestCase( TestFailureTest::CopyConstructor ),
		TestCase( TestFailureTest::CopyAssignmentOperator ),
		TestCase()
	};

	/**	\brief Array of test function tests. */
	TestCase testFuncTests[] =
	{
		TestCase( "IsTrue( true )", IsTrueTest ),
		TestCase( "IsTrue( false )", IsTrueFailTest ),
		TestCase( "IsFalse( false )", IsFalseTest ),
		TestCase( "IsFalse( true )", IsFalseFailTest ),
		TestCase( "IsEqual( true )", IsEqualTest ),
		TestCase( "IsEqual( false )", IsEqualFailTest ),
		TestCase( "IsNotEqual( false )", IsNotEqualTest ),
		TestCase( "IsNotEqual( true )", IsNotEqualFailTest ),
		TestCase( "IsEqual missing operator<<", IsEqualMissingOutputOperator ),
		TestCase( "IsNotEqual missing operator<<", IsNotEqualMissingOutputOperator ),		
		TestCase( "Failure", FailureTest ),
		TestCase( "MissingTest", MissingTestTest ),
		TestCase()
	};

	/**	\brief Array of throws exception tests. */
	TestCase throwsExceptionTests[] =
	{
		TestCase( "THROWS_EXCEPTION( throw std::bad_alloc;, std::bad_alloc )", ThrowsExceptionTest ),
		TestCase( "THROWS_EXCEPTION( \"\", std::bad_alloc )", ThrowsExceptionFailTest ),		
		TestCase( "DOES_NOT_THROW_EXCEPTION( \"\" )", DoesNotThrowExceptionTest ),		
		TestCase( "DOES_NOT_THROW_EXCEPTION( throw std::bad_alloc() )", DoesNotThrowExceptionFailTest ),
		TestCase( "THROWS_EXCEPTION( Thrower< std::exception >(), std::bad_alloc )", ThrowsExceptionWrongExceptionTest ),
		
		TestCase()
	};

	/**	\brief Array of context object tests. */
	TestCase contextObjectTests[] = 
	{
		TestCase( "Function", FunctionPtr( ContextObjectFunc, lifeTheUniverseAndEverything ) ),
		TestCase( "Class", Incarnate( &ContextObjectClass::Run, lifeTheUniverseAndEverything ) ),
		TestCase()
	};

	/**	\brief Array of SimpleDate tests. */
	TestCase simpleDateTests[] =
	{
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::BasicTest ) ) ),
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::ExceptionTest ) ) ),
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::IsLeapYearTest ) ) ),	
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::DayOfWeekTest ) ) ),	
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::IntervalTest ) ) ),
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::OperatorTests ) ) ),		
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::ToIsoDateTest ) ) ),
		TestCase( TestCase( USE_NAME( utility::test::SimpleDateTest::EmptyDateTest ) ) ),
		TestCase()
	};

	/**	\brief Array of TestRunner tests. */
	TestCase testRunnerTests[] =
	{
		TestCase( TestCase( USE_NAME( TestRunnerTest::RunByNameTest ) ) ),
		TestCase( TestCase( USE_NAME( TestRunnerTest::RunByNameTestNotFoundTest ) ) ),	
		TestCase( TestCase( USE_NAME( TestRunnerTest::DuplicateTestNameFoundTest ) ) ),		
		TestCase( TestCase( USE_NAME( TestRunnerTest::RunByTestSetNameTest ) ) ),
		TestCase( TestCase( USE_NAME( TestRunnerTest::RunByTestSetNameTestNotFoundTest ) ) ),
		TestCase( TestCase( USE_NAME( TestRunnerTest::DuplicateTestSetNameFoundTest ) ) ),
		TestCase( TestCase( USE_NAME( TestRunnerTest::ComandLineParserTestsTest ) ) ),		
		TestCase( TestCase( USE_NAME( TestRunnerTest::ComandLineParserTestSetTest ) ) ),
		TestCase( TestCase( USE_NAME( TestRunnerTest::ComandLineParserTestsAndTestSetsTest ) ) ),		
		TestCase()
	};

	/**	\brief Array of ComandLineParser tests. */
	TestCase commandLineParserTests[] =
	{
		TestCase( TestCase( USE_NAME( CommandLineParserTestShort ) ) ),
		TestCase( TestCase( USE_NAME( CommandLineParserTestLong ) ) ),
		TestCase()
	};

	void AddTests
	( 
		Aeryn::TestRunner& testRunner 
	)
	{
		testRunner.Add( USE_NAME( reportTests ) );		
		testRunner.Add( testFailureTests );
		testRunner.Add( "Test Function Tests", testFuncTests );
		testRunner.Add( "Throws Exception Tests", throwsExceptionTests );		
		testRunner.Add( "Context object tests", contextObjectTests );	
		testRunner.Add( USE_NAME( simpleDateTests ) );
		testRunner.Add( USE_NAME( testRunnerTests ) );
		testRunner.Add( USE_NAME( commandLineParserTests ) );
	}	
}
