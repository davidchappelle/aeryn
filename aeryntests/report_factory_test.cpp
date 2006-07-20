

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

/** \file report_factory_test.cpp
 *  \brief ReportFactoryTest Definition.
 */

#include "report_factory_test.hpp"
#include <aeryn/report_factory.hpp>
#include <aeryn/bad_report_name.hpp>
#include <aeryn/failed.hpp>
#include <aeryn/is_true.hpp>
#include <aeryn/is_equal.hpp>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		/**	\brief Fake report object. */
		class CustomReport : public IReport
		{
		public:
			static std::string Name
				()
			{
				return "report factory test report";
			}

			/**	Constructor */
			explicit CustomReport
				()
			{
			}

			virtual void BeginTesting
				( const std::string&,
				  unsigned long )
			{
			}

			virtual void BeginTestSet
				( const std::string& )
			{
			}

			virtual void BeginTest
				( const std::string& )
			{
			}

			virtual void Pass
				( const std::string& )
			{
			}

			virtual void Failure
				(  const std::string&,
				  const TestFailure& )
			{
			}

			virtual void MissingTest
				(  const std::string&,
				  const TestMissing& )
			{
			}

			virtual void Error
				( const std::string&,
				  const std::string& )
			{
			}

			virtual void EndTest
				( const std::string& )
			{
			}

			virtual void EndTestSet
				( const std::string& )
			{
			}

			virtual void EndTesting
				( unsigned long, 
				  unsigned long,
				  unsigned long )
			{
			}
		};

		/**	\brief Customer Report factory. */
		class CustomReportFactory : public ReportFactory
		{
		public:
			/**	\brief Contructor
			 *
			 *	Adds custom report to report map.
			 */
			explicit CustomReportFactory
				() : ReportFactory()
			{
				Add( CustomReport::Name(), &CreateCustomReport );
			}

		private:
			/**	\brief Creates an instance of the custom report.
			 *
			 *	\return An instance of the custom report.
			 */
			static IReportPtr CreateCustomReport
				()
			{
				return IReportPtr( new CustomReport );
			}
		};

	}	
	
	//////////////////////////////////////////////////////////////////////////
	void ReportFactoryTest::StandardReportTests
			()
	{
		try
		{
			ReportFactory reportFactory;

			IS_TRUE( 0 != reportFactory.Create( "" ).get() ); // Make sure you get a report if no name is specified.
			IS_TRUE( 0 != reportFactory.Create( MinimalReport::Name() ).get() );
			IS_TRUE( 0 != reportFactory.Create( TerseReport::Name() ).get() );
			IS_TRUE( 0 != reportFactory.Create( VerboseReport::Name() ).get() );
			IS_TRUE( 0 != reportFactory.Create( XcodeReport<>::Name() ).get() );
			IS_TRUE( 0 != reportFactory.Create( ReportFactory::DefaultTestName() ).get() );
		}
		catch( const BadReportName& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void ReportFactoryTest::InvalidReportNameTest
			()
	{
		const std::string invalidReportname = "invalid report";
		
		try
		{
			ReportFactory reportFactory;			
			reportFactory.Create( invalidReportname ).get();
			FAILED( "Valid report was created from an invalid name!" );
		}
		catch( const BadReportName& e )
		{
			IS_EQUAL( "\"" + invalidReportname + "\" is not a valid report name.", e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void ReportFactoryTest::CustomReportFactoryTest
			()
	{
		try
		{
			CustomReportFactory reportFactory;			
			IS_TRUE( 0 != reportFactory.Create( CustomReport::Name() ).get() );
			
		}
		catch( const BadReportName& e )
		{
			FAILED( e.what() );
		}
	}

	//////////////////////////////////////////////////////////////////////////
}
