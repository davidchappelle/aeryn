
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

/** \file test_set_cont.cpp
 *  \brief Definition of TestSetCont.
 */

#include "test_set_cont.hpp"
#include <algorithm>

namespace Aeryn
{
	namespace
	{
		/**	\brief Default test set name. */
		static const std::string defaultTestSetName = "Test Set";

		/**	\brief Functor to count number of test cases.
		 *
		 *	A better solution would be to use std::accumulate and an
		 *	appropriate predicate. However, std::accumulate is not
		 *	implemented correctly on for compilers, so this 
		 *	std::for_each solution works just as well.
		 */
		class AccumTestCount
		{
		private:
			/**	\brief A reference to an object to hold the result. */
			size_t& count_;

		public:
			/**	\brief Constructor 
			 *
			 *	\param count A reference to an object to hold the result.
			 */
			AccumTestCount( size_t& count )
			: count_(count)
			{}

			/**	\brief Function operator.
			 *
			 *	Adds the number of tests in the supplied test set to
			 *	the total count.
			 *
			 *	\brief testSet A test set.
			 */
			void operator()(TestSetCont::TestSet testSet )
			{
				count_ += testSet.first.size();
			}
		};
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetCont::TestSetCont()
	: testSets_(),
	   defaultTestSetCount_( 1 )
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetCont::AddTests
	( 
		const std::string& name,
		const TestCase nullTerminatedArray[] 
	)
	{
		TestCaseCont testSet;

		for( unsigned long i = 0; !nullTerminatedArray[i].IsNull(); ++i )
		{
			testSet.push_back( nullTerminatedArray[i] );
		}

		testSets_.push_back( TestSet( testSet, name ) );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetCont::AddTests
	( 
		const TestCase nullTerminatedArray[] 
	)
	{
		AddTests( NextTestSetName(), nullTerminatedArray );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetCont::AddTest
	( 
		const std::string& name, 
		const TestCase& singleTestCase 
	)
	{
		TestCaseCont testSet;
		testSet.push_back( singleTestCase );
		testSets_.push_back( TestSet( testSet, name ) );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetCont::AddTest
	( 
		const TestCase& singleTestCase 
	)
	{
		AddTest( NextTestSetName(), singleTestCase );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetCont::AddTestSet
	( 
		const TestSet& testSet 
	)
	{
		testSets_.push_back( testSet );
	}

	//////////////////////////////////////////////////////////////////////////
	void TestSetCont::AddTestSet
	( 
		const std::string& testSetName,
		const TestCase& test 
	)
	{
		TestCaseCont tests;
		tests.push_back( test );
		testSets_.push_back( TestSet( tests, testSetName ) );
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetCont::SizeType TestSetCont::TestCount
		() const
	{
		size_t count = 0;
		AccumTestCount accumTestCount(count);
		std::for_each(testSets_.begin(), testSets_.end(), accumTestCount );
		return count;
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetCont::ConstItr TestSetCont::Begin
		() const
	{
		return testSets_.begin();
	}

	//////////////////////////////////////////////////////////////////////////
	TestSetCont::ConstItr TestSetCont::End
		() const
	{
		return testSets_.end();
	}

	//////////////////////////////////////////////////////////////////////////
	TestCase TestSetCont::FindTest
	( 
		const std::string& name,
		std::string& testSetName 
	) const
	{
		TestSetCont::ConstItr currentTestSet	= testSets_.begin();
		TestSetCont::ConstItr endTestSet		= testSets_.end();

		for( ; currentTestSet != endTestSet; ++currentTestSet )
		{
			TestCaseCont::const_iterator current	= currentTestSet->first.begin();
			TestCaseCont::const_iterator end		= currentTestSet->first.end();

			for( ; current != end; ++current )
			{
				if ( name == current->Name() )
				{
					testSetName = currentTestSet->second;
					return *current;
				}
			}
		}

		return TestCase();
	}

	//////////////////////////////////////////////////////////////////////////
	bool TestSetCont::IsTestNameUnique
	( 
		const std::string& name 
	) const
	{
		TestCaseCont::size_type count = 0;

		TestSetCont::ConstItr currentTestSet	= testSets_.begin();
		TestSetCont::ConstItr endTestSet		= testSets_.end();

		for( ; currentTestSet != endTestSet; ++currentTestSet )
		{
			TestCaseCont::const_iterator current	= currentTestSet->first.begin();
			TestCaseCont::const_iterator end		= currentTestSet->first.end();

			for( ; current != end; ++current )
			{
				if ( name == current->Name() )
				{
					++count;
				}
			}
		}

		return count <= 1;
	}

	//////////////////////////////////////////////////////////////////////////
	bool TestSetCont::FindTestSetByName
	( 
		const std::string& name, 
		TestSet& testSet 
	) const
	{
		TestSetCont::ConstItr current	= testSets_.begin();
		TestSetCont::ConstItr end		= testSets_.end();

		for(; current != end; ++current )
		{
			if ( name == current->second )
			{
				testSet = *current;
				return true;
			}
		}

		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	bool TestSetCont::IsTestSetNameUnique
	( 
		const std::string& name 
	) const
	{
		TestSetCont::SizeType count = 0;

		TestSetCont::ConstItr current	= testSets_.begin();
		TestSetCont::ConstItr end		= testSets_.end();

		for( ; current != end; ++current )
		{
			if ( name == current->second )
			{
				++count;
			}		
		}

		return count <= 1;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string TestSetCont::NextTestSetName
		()
	{
		std::stringstream str;
		str << defaultTestSetName << " " << defaultTestSetCount_;
		++defaultTestSetCount_;
		return str.str();
	}
}
