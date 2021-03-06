
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

/** \file report_factory_test.hpp
 *  \brief ReportFactoryTest declaration.
 */	

#ifndef AERYN_REPORT_FACTORY_TEST_HPP
#define AERYN_REPORT_FACTORY_TEST_HPP

namespace Aeryn
{
	/**	\brief ReportFactoryTests. */
	class ReportFactoryTest
	{
	public:
		/**	\brief Tests creation of standard reports. */
		static void StandardReportTests
			();

		/**	\brief Test for invalid report names. */
		static void InvalidReportNameTest
			();

		/**	\brief Test for customer report factory mechanism. */
		static void CustomReportFactoryTest
			();
	};
}

#endif // AERYN_REPORT_FACTORY_TEST_HPP
