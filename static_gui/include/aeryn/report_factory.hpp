
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

/** \file report_factory.hpp
 *  \brief ReportFactory declaration.
 */	

#ifndef AERYN_REPORT_FACTORY_H
#define AERYN_REPORT_FACTORY_H

#include <aeryn/minimal_report.hpp>
#include <aeryn/terse_report.hpp>
#include <aeryn/verbose_report.hpp>
#include <aeryn/xcode_report.hpp>
#include <aeryn/ireport.hpp>
#include <map>
#include <cassert>

namespace Aeryn
{
	/**	\brief Factory for creating reports. */
	class ReportFactory
	{
	public:
		/**	\brief Report smart pointer.
		 *
		 *	Used to automatically manage dynamically allocated report objects.
		 */
		typedef std::auto_ptr< IReport > IReportPtr;

	private:
		/**	\brief Report map type. */
		typedef std::map< std::string, IReportPtr(*)() > ReportMap;

		/**	\brief The name of the default test. */
		static const std::string defaultTestName;

		/** \brief Map of reports onto report name. */
		ReportMap reportMap;

	public:
		/**	\brief Accessor for default test name.
		 *
		 *	Returns a string containing the default test name.
		 */
		static std::string DefaultTestName
			();


        /**	\brief Constructor.
		 *
		 *	Constructs default report map.
		 */
		explicit ReportFactory
			();

		/**	\brief Creates a report based on command line parameters.
		 * 
		 *	\return An IReportPtr pointing to an instance of a report.
		 */
		IReportPtr Create
			( const std::string& name ) const;

	protected:
		/**	\brief Adds a new name to report map.
		 *
		 *	\param name The name to give the report.
		 *	\param func The function that creates the report.
		 */
		void Add
			( const std::string& name, 
			  IReportPtr(*func)() );

	private:
		/**	\brief Creates a in instance of MinimalReport.
		 *
		 *	\return An instance of MinimalReport.
		 */
		static IReportPtr CreateMinimalReport
			();

		/**	\brief Creates a in instance of TerseReport.
		 *
		 *	\return An instance of TerseReport.
		 */
		static IReportPtr CreateTerseReport
			();

		/**	\brief Creates a in instance of VerboseReport.
		 *
		 *	\return An instance of VerboseReport.
		 */
		static IReportPtr CreateVerboseReport
			();

		/**	\brief Creates a in instance of VerboseReport.
		 *
		 *	\return An instance of VerboseReport.
		 */
		static IReportPtr CreateXCodeReport
			();	
	};

}

#endif // AERYN_REPORT_FACTORY_H
