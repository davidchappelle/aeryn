
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

/** \file examples\minimaltest\main.cpp
 *  \brief Example of the least amount of code needed to run a test.
 */	

#include <aeryn/test_runner.hpp>
#include <aeryn/is_equal.hpp>
#include <aeryn/use_name.hpp>

/**	\brief Simple function based test fixture. 
 *
 *	<code><pre>
 *	void TestForTheMeaningOfLife()
 *	{
 *		const int theMeaningofLife = 42;
 *		IS_EQUAL( theMeaningofLife, 42 );
 *	}
 *	</pre></code>
 */
void TestForTheMeaningOfLife()
{
	const int theMeaningofLife = 42;
	IS_EQUAL( theMeaningofLife, 42 );
}

/**	\brief Example of the least amount of code needed in a main() function to run tests. 
 *
 *	<code><pre>
 *	int main()
 *	{
 *		using namespace Aeryn;
 *		TestRunner testRunner;
 *		testRunner.Add( TestCase( USE_NAME( TestForTheMeaningOfLife ) ) );
 *		return testRunner.Run();
 *	}
 *	</pre></code>
 */
int main()
{
	using namespace Aeryn;
	TestRunner testRunner;
	testRunner.Add( TestCase( USE_NAME( TestForTheMeaningOfLife ) ) );
	return testRunner.Run();
}
