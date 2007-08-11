
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

/** \file report_factory.dpp
 *  \brief ReportFactory definition.
 */	

#include <aeryn/report_factory.hpp>
#include <aeryn/bad_report_name.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	const char* ReportFactory::defaultTestName = "default";

	//////////////////////////////////////////////////////////////////////////
	std::string ReportFactory::DefaultTestName
			()
	{
		return defaultTestName;
	}
	
	ReportFactory::ReportFactory()
			: reportMap()
	{
		Add( DefaultTestName(), &CreateMinimalReport );
		Add( MinimalReport::Name(), &CreateMinimalReport );
		Add( TerseReport::Name(), &CreateTerseReport );
		Add( VerboseReport::Name(), &CreateVerboseReport );
		Add( XcodeReport<>::Name(), &CreateXCodeReport );
	}

	//////////////////////////////////////////////////////////////////////////
	ReportFactory::IReportPtr ReportFactory::CreateMinimalReport
		()
	{
		return IReportPtr( new MinimalReport );
	}

	//////////////////////////////////////////////////////////////////////////
	ReportFactory::IReportPtr ReportFactory::CreateTerseReport()
	{
		return IReportPtr( new TerseReport );
	}

	//////////////////////////////////////////////////////////////////////////
	ReportFactory::IReportPtr ReportFactory::CreateVerboseReport
		()
	{
		return IReportPtr( new VerboseReport );
	}

	//////////////////////////////////////////////////////////////////////////
	ReportFactory::IReportPtr ReportFactory::CreateXCodeReport
		()
	{
		return IReportPtr( new XcodeReport<>( std::cout, "bin/TestPassCookie.txt" ) );
	}

	//////////////////////////////////////////////////////////////////////////
	ReportFactory::IReportPtr ReportFactory::Create
	( 
		const std::string& name 
	) const
	{
		IReportPtr report;
		ReportMap::const_iterator func = reportMap.find( name );
		if (  func != reportMap.end() )
		{
			report = func->second();
		}
		else
		{
			if ( name.empty() )
			{
				func = reportMap.find( defaultTestName );
				if (  func != reportMap.end() )
				{
					report = func->second();
				}
				else
				{
					throw BadReportName( defaultTestName );
				}
			}
			else
			{
				throw BadReportName( name );
			}
		}

		assert( 0 != report.get() );
		return report;
	}

	//////////////////////////////////////////////////////////////////////////
	void ReportFactory::Add
	( 
		const std::string& name, 
		IReportPtr(*func)() 
	)
	{
		reportMap[name] = func;
	}

	//////////////////////////////////////////////////////////////////////////		
}
