
/*
 *  Aeryn - C++ Testing Framework
 *  Copyright (C) 2006 Paul Grenyer
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

/** \file command_line_test_set_builder.hpp
 *  \brief Declaration of TestSetCont.
 */

#ifndef AERYN_COMMAND_LINE_TEST_SET_BUILDER_H
#define AERYN_COMMAND_LINE_TEST_SET_BUILDER_H

#include "test_set_cont.hpp"
#include <aeryn/test_case.hpp>
#include <aeryn/command_line_parser.hpp>
#include <map>
#include <string>

namespace Aeryn
{
	/**	\brief Finds a test by name.
	 *
	 *	\param name The name of the test to find.
	 *	\param testSets The test sets to search in.
	 *	\param testSetName A reference to a string to take the name of the test set
	 * 	that the test belongs too.
	 * 
	 *	\return The test if found otherwise TestCase().
	 *
	 *	\throws DuplicateTestNameFound If the test name is not unique.
	 *	\throws TestNameNotFound If the test cannot be found.
	 */
	TestCase FindTestByName
		( const std::string& name,
		  const TestSetCont& testSets,
		  std::string &testSetName );
	
	/**	\brief Finds a test set by name.
	 *
	 *	\param name The name of the test set to find.
	 *	\param testSets A reference to a TestSet object to take the test set if found.
	 *
	 *	\return True if the test set is found, otherwise false.
	 *
	 *	\throws DuplicateTestSetNameFound If the test set name is not unique.
	 *	\throws TestSetNameNotFound If the test set cannot be found.
	 */
	TestSetCont::TestSet FindTestSetByName
		( const std::string& name,
		  const TestSetCont& testSets );	
	
	/**	\brief Constructs a test set from the supplied command line object. */
	class CommandLineTestSetBuilder : private Utils::Noncopyable
	{
	private:
		/**	\brief A map of test case containers. */
		typedef std::map< std::string, TestSetCont::TestCaseCont > TestCaseContMap;

		/**	\brief A reference to the command line object. */
		const CommandLineParser& commandLine_;

		/**	\brief The master list of test sets.*/
		const TestSetCont& testSets_;

		/**	\brief The list of test sets to be run. */
		TestSetCont& testSetsToRun_;

	public:
		/**	\brief Constructor
		 *
		 *	Constructs a test set from the supplied command line object. 
		 *
		 *	\param commandLine A reference to the command line object.
		 *	\param testSets The master list of test sets.
		 *	\param testSetsToRun The list of test sets to be run. 
		 *
		 *	\throws DuplicateTestNameFound If a test name is not unique.
		 *	\throws TestNameNotFound If a test cannot be found.
		 *	\throws DuplicateTestSetNameFound If a test set name is not unique.
		 *	\throws TestSetNameNotFound If the a set cannot be found.
		 */
		explicit CommandLineTestSetBuilder
			( const CommandLineParser& commandLine,
			  const TestSetCont& testSets,
			  TestSetCont& testSetsToRun );

		/**	\brief Adds the test sets from the command line object to the test set.
		 *
		 *	\throws DuplicateTestSetNameFound If a test set name is not unique.
		 *	\throws TestSetNameNotFound If the a set cannot be found.
		 */
		void AddTestSets
			();

		/**	\brief Adds the tests from the command line object to the test set.
		 *
		 *	\throws DuplicateTestNameFound If a test name is not unique.
		 *	\throws TestNameNotFound If a test cannot be found.
		 */
		void AddTests
			();

		/**	\brief Groups the individual tests into thier test set group.
		 *	
		 *	\return The test sets to add.
		 *
		 *	\throws DuplicateTestNameFound If a test name is not unique.
		 *	\throws TestNameNotFound If a test cannot be found.
		 */
		TestCaseContMap GenerateTestTestSets
			() const;
	};
}

#endif // AERYN_COMMAND_LINE_TEST_SET_BUILDER_H
