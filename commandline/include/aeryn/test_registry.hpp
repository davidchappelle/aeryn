
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

/** \file test_registry.hpp
 *  \brief TestRegistry declaration and associated macros.
 */	

#ifndef AERYN_TEST_REGISTRY_H
#define AERYN_TEST_REGISTRY_H

#include <aeryn/details/noncopyable.hpp>
#include <aeryn/test_runner.hpp>
#include <aeryn/details/preprocessor.hpp>
#include <aeryn/use_name.hpp>

namespace Aeryn
{
	/**	\brief Test registry
	 *
	 *	The test registry as a singleton wrapper for test runner. Its use is optional and intended for
	 *	for people who want to be able add tests to the test runner anywhere in the code.
	 */
	class TestRegistry : private Utils::Noncopyable
	{
	public:
		/**	\brief Test runner accessor. */
		static TestRunner& GetTestRunner
			();

		/**	\brief Generic forwarding function for TestRunner Add functions taking a single parameter. */
		template<class A>
		static void Add
			(A a)
		{
			GetTestRunner().Add(a);
		}

		/**	\brief Generic forwarding function for TestRunner Add functions taking a two parameters. */
		template<class A, class B>
		static void Add
			(A a, B b)
		{
			GetTestRunner().Add(a, b);
		}

		/**	\brief Register
		 *
		 *	Every time a test case or a set of test cases are added to the test runner via
		 *	the test registry a unique instance of Register is created to and used to actually
		 *	add the test cases.
		 */
		class Register : public Utils::Noncopyable
		{
		   public:
			   /**	\brief  Forwards parameters on to the TestRegistry's internal TestRunner::Add */
			   template<class A>
				   Register
				   (A a)
			   {
				   TestRegistry::GetTestRunner().Add(a);
			   }

			   /**	\brief Overload for two parameters to TestRunner::Add. */
			   template<class A, class B>
				   Register
				   (A a, B b)
			   {
				   TestRegistry::GetTestRunner().Add(a, b);
			   }
		   };

	private:
		/**	\brief Private constructor to prevent TestRegistry from being instantiated. */
		TestRegistry();
	};

/**	\brief REGISTER_TESTS
 *	
 *	Macro to simplify test registration with the TestRegistry.
 *	Rather than creating a global RegisterTests helper, you can chose to
 *	use this macro to do it for you (it's largely a matter of taste
 *	which one you think is more readable in your code).
 *	
 *	To use the macro write something like:
 *	<code><pre>
 *	   TestCase tests[] =
 *	   {
 *	       ...
 *	   };
 *	   REGISTER_TESTS(tests)
 *	</pre></code>
 *	
 *	 @see TestRegistry
 */
#define REGISTER_TESTS(tests) REGISTER_TESTS_2(tests, AERYN_UNIQUE_NAME(tests))

/**	\brief Helper for REGISTER_TESTS
 *
 *	@internal
 *	@see REGISTER_TESTS
 */
#define REGISTER_TESTS_2(tests, name) REGISTER_TESTS_3(tests, name)

/**	\brief Helper for REGISTER_TESTS
 *
 *	@internal
 *	@see REGISTER_TESTS
 */
#define REGISTER_TESTS_3(tests, name) \
	static ::Aeryn::TestRegistry::Register autoRegisterTest_##name(tests)

/**	\brief A version of REGISTER_TESTS that allows a name to be specified.
 *
 *	@internal
 *	@see REGISTER_TESTS
 */
#define REGISTER_TESTS_WITH_NAME( testName, tests ) REGISTER_TESTS_WITH_NAME_2( testName, tests, AERYN_UNIQUE_NAME(tests) )

/**	\brief Helper for REGISTER_TESTS_WITH_NAME and REGISTER_TESTS_USE_NAME.
 *
 *	@internal
 *	@see REGISTER_TESTS_WITH_NAME
 *	@see REGISTER_TESTS_USE_NAME
 */
#define REGISTER_TESTS_WITH_NAME_2( testName, tests, name ) REGISTER_TESTS_WITH_NAME_3( testName, tests, name )

/**	\brief Helper for REGISTER_TESTS_WITH_NAME and REGISTER_TESTS_USE_NAME.
 *
 *	@internal
 *	@see REGISTER_TESTS_WITH_NAME
 *	@see REGISTER_TESTS_USE_NAME
 */
#define REGISTER_TESTS_WITH_NAME_3( testName, tests, name ) \
	static ::Aeryn::TestRegistry::Register autoRegisterTest_##name( testName, tests )

/**	\brief A version of REGISTER_TESTS that uses the name of a test fixture function to 
 *	generate a name for the test case.
 *
 *	@internal
 *	@see REGISTER_TESTS
 */
#define REGISTER_TESTS_USE_NAME( tests ) REGISTER_TESTS_WITH_NAME_2( ::Aeryn::FormatName( #tests ), tests, AERYN_UNIQUE_NAME(tests))

}

#endif // AERYN_TEST_REGISTRY_H
