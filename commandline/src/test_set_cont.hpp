
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

/** \file test_set_cont.hpp
 *  \brief Declaration of TestSetCont.
 */

#ifndef AERYN_TEST_SET_CONT_H
#define AERYN_TEST_SET_CONT_H

#include <aeryn/details/noncopyable.hpp>
#include <aeryn/test_case.hpp>
#include <string>
#include <vector>

namespace Aeryn
{
	/**	\brief TestSet container. */
	class TestSetCont : private Utils::Noncopyable
	{
	public:
		/**	\brief TestCase container type. */
		typedef std::vector< TestCase >	TestCaseCont;

		/**	\brief TestSet type. */
		typedef std::pair< TestCaseCont, std::string >	TestSet;		

	private:
		/**	\brief test set container type. */
		typedef std::vector< TestSet > CONT;

		/**	\brief Store for test sets. */
		CONT testSets_;

		unsigned long defaultTestSetCount_;

	public:
		/**	\brief test set container constant iterator. */
		typedef CONT::const_iterator ConstItr;

		/**	\brief test set container size type. */
		typedef CONT::size_type SizeType;

		/**	\brief Default constructor. */
		explicit TestSetCont
			();

		/**	\brief Adds a set of tests and gives it a name. 
		 *
		 *	\param name The test set name.
		 *	\param nullTerminatedArray A null terminated array of TestCase's.
		 */
		void AddTests
			( const std::string& name,
			  const TestCase nullTerminatedArray[] );

		/**	\brief Adds a set of tests.
		 *
		 *	\param nullTerminatedArray A null terminated array of TestCase's.
		 */
		void AddTests
			( const TestCase nullTerminatedArray[] );

		/**	\brief Adds a single test case and gives it a name. 
		 *
		 *	\param name The test case name.
		 *	\param singleTestCase A null terminated array of TestCase's.
		 */
		void AddTest
			( const std::string& name, 
			  const TestCase& singleTestCase );

		/**	\brief Adds a single test case.
		 *
		 *	\param singleTestCase A null terminated array of TestCase's.
		 */
		void AddTest
			( const TestCase& singleTestCase );

		/**	\brief Adds a test set.
		 *
		 *	\param testSet The TestSet to add.
		 */
		void AddTestSet
			( const TestSet& testSet );

		/**	\brief Adds a test set and gives it a name.
		 *
		 *	\param testSetName The name to give the test set.
		 *	\param testSet The TestSet to add.
		 */
		void AddTestSet
			( const std::string& testSetName,
			  const TestCase& test );

		/**	\brief Gives the number of test cases. */
		SizeType TestCount
			() const;

		/**	\brief Gets the begin iterator. 
		 *
		 *	\return The begin iterator.
		 */
		ConstItr Begin
			() const;

		/**	\brief Gets the end iterator. 
		 *
		 *	\return The end iterator.
		 */
		ConstItr End
			() const;

		/**	\brief Finds a test by name.
		 *
		 *	\param name The name of the test to find.
		 *	\param testSetName A reference to a string to take the name of the test set
		 *	that the test belongs too.
		 *	\return The test if found otherwise TestCase().
		 */
		TestCase FindTest
		( 
			const std::string& name,
			std::string& testSetName 
		) const;

		/**	\brief Determines if the specified test name is unique.
		 *
		 *	\param name The test name to search for.
		 *	\return true if the name is unique, otherwise false.
		 */
		bool IsTestNameUnique
		( 
			const std::string& name 
		) const;

		/**	\brief Finds a test set by name.
		 *
		 *	\param name The name of the test set to find.
		 *	\param testSet A reference to a TestSet object to take the test set if found.
		 *	\return True if the test set is found, otherwise false.
		 */
		bool FindTestSetByName
		( 
			const std::string& name, 
			TestSet& testSet 
		) const;


		/**	\brief Determines if the specified test set name is unique.
		 *
		 *	\param name The test set name to search for.
		 *	\return true if the name is unique, otherwise false.
		 */
		bool IsTestSetNameUnique
		( 
			const std::string& name 
		) const;

	private:
		/**	\brief Generates the next unique test set name. */
		std::string NextTestSetName
			();
	};
}

#endif // AERYN_TEST_SET_CONT_H
