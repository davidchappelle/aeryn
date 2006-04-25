
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

/** \file simple_date_test.cpp
 *  \brief SimpleDateTest definition.
 */	
#include <iostream>

#include <aeryn/is_equal.hpp>
#include <aeryn/is_true.hpp>
#include <aeryn/is_false.hpp>
#include <aeryn/throws_exception.hpp>
#include <aeryn/does_not_throw_exception.hpp>
#include <aeryn/use_name.hpp>
#include <aeryn/test_runner.hpp>

#include "simple_date_test.hpp"
#include "simple_date.hpp"

//-----------------------------------------------------------------------------
namespace utility
{
	namespace test
	{
		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::BasicTest()
		{
			simple_date d2( year( 1970 ), apr, 18 );
			IS_EQUAL( 18, d2.get_day() );
			IS_EQUAL( apr, d2.get_month() );
			IS_EQUAL( 1970, d2.get_year().value );

			d2 = simple_date( year( 2005 ), jan, 31 );
			IS_EQUAL( 31, d2.get_day() );
			IS_EQUAL( jan, d2.get_month() );
			IS_EQUAL( 2005, d2.get_year().value );

			d2 = simple_date( year( 1901 ), may, 1 );
			IS_EQUAL( 1, d2.get_day() );
			IS_EQUAL( may, d2.get_month() );
			IS_EQUAL( 1901, d2.get_year().value );
		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::ExceptionTest()
		{
			THROWS_EXCEPTION( (simple_date( year( 1581 ), month( 1 ), 10 ) ), date_exception );

			THROWS_EXCEPTION( (simple_date( year( 2000 ), month( -1 ), 10 ) ), date_exception );
			THROWS_EXCEPTION( (simple_date( year( 2000 ), month( 12 ), 10 ) ), date_exception );

			THROWS_EXCEPTION( (simple_date( year( 2000 ), feb, 30 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), feb, 29 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), feb, 29 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2001 ), feb, 28 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), jan, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), jan, 31 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), mar, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), mar, 31 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), apr, 31 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), apr, 30 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), may, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), may, 31 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), jun, 31 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), jun, 30 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), jul, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), jul, 31 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), aug, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), aug, 31 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), sep, 31 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), sep, 30 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), oct, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), oct, 31 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), nov, 31 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), nov, 30 ) ) );

			THROWS_EXCEPTION( (simple_date( year( 2001 ), dec, 32 ) ), date_exception );
			DOES_NOT_THROW_EXCEPTION( (simple_date( year( 2000 ), dec, 31 ) ) );
		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::IsLeapYearTest()
		{
			IS_TRUE( is_leap_year( year( 1988 ) ) );
			IS_TRUE( is_leap_year( year( 2000 ) ) );
			IS_TRUE( is_leap_year( year( 2004 ) ) );
			IS_TRUE( ! is_leap_year( year( 1987 ) ) );
			IS_TRUE( ! is_leap_year( year( 2001 ) ) );
			IS_TRUE( ! is_leap_year( year( 1800 ) ) );
		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::DayOfWeekTest()
		{
			simple_date d( year( 2005 ), may, 25 );
			IS_EQUAL( wed, d.get_day_of_week() );

			// first UK lottery draw
			d = simple_date( year( 1994 ), nov, 19 );
			IS_EQUAL( sat, d.get_day_of_week() );

			// A wednesday UK lottery draw
			d = simple_date( year( 2004 ), dec, 29 );
			IS_EQUAL( wed, d.get_day_of_week() );
		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::IntervalTest()
		{
			simple_date d1( year( 1901 ), may, 1 );

			date_interval di = 10;
			d1 += di;
			IS_EQUAL( 11, d1.get_day() );
			d1 -= 5;
			IS_EQUAL( 6, d1.get_day() );

			simple_date d2( year( 2000 ), jun, 10 );
			simple_date d3( year( 2000 ), jul, 10 );
			simple_date d4( year( 2001 ), mar, 10 );
			simple_date d5( year( 2001 ), feb, 10 );

			IS_EQUAL( date_interval( -30 ), d2 - d3 );
			IS_EQUAL( date_interval( 28 ), d4 - d5 );

			simple_date d6( year( 2000 ), feb, 10 );
			simple_date d7( year( 2000 ), mar, 10 );
			IS_EQUAL( date_interval( -29 ), d6 - d7 );

		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::OperatorTests()
		{
			simple_date d1( year( 2000 ), dec, 24 );
			d1 += 365;
			simple_date d2( year( 2001 ), dec, 24 );
			IS_EQUAL( d2, d1 );
			d2 -= 365;

			IS_TRUE( d1 > d2 );
			IS_TRUE( d2 < d1 );
			IS_TRUE( d1 != d2 );
			IS_FALSE( d1 == d2 );
		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::ToIsoDateTest()
		{
			simple_date d( year( 2001 ), dec, 24 );

			IS_EQUAL( 20011224, to_iso_date( d ) );
			IS_EQUAL( 19990101, to_iso_date( simple_date( year( 1999 ), jan, 1 ) ) );
		}

		//////////////////////////////////////////////////////////////////////////
		void SimpleDateTest::EmptyDateTest()
		{
			simple_date d( year( 2001 ), dec, 24 );			
			simple_date empty;
        	IS_TRUE( d > empty );
			IS_TRUE( empty < d );			
		}

		//////////////////////////////////////////////////////////////////////////		

	}
}

//-----------------------------------------------------------------------------
