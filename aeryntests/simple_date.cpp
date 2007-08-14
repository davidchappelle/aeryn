
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

//-----------------------------------------------------------------------------
/** \file       simple_date.cpp
 *  \brief		simple_date implementation.
 *  \author     Steve Love
 *  \date       May 2005
 */

//-----------------------------------------------------------------------------

#include "simple_date.hpp"

//-----------------------------------------------------------------------------
namespace utility
{
    /** Create a primitive year from the provided number. No check is made
     *  for validity.
     *  When a year object is passed into the simple_date constructor, the
     *  validity check is made at that point. Therefore year objects can
     *  be any value.
     */
	year::year( int v )
		: value( v )
	{
	}

//-----------------------------------------------------------------------------

    /** Create a date_interval.
     *  Date interval objects should generally be only created by the 
     *  simple_date class; the value for the constructor is merely the
     *  difference between two julian numbers, which are stored as doubles
     *  internally.
     */
	date_interval::date_interval( double diff )
		: value( diff )
	{
	}

    /** Access the number of days represented by the date_interval.
     *  A single day is the finest granularity shown by an interval.
     *  Technically this could be made finer since the stored double would
     *  allow it.
     */
	int date_interval::days() const
	{
		return static_cast< int >( value );
	}

    /** Determine if two date_interval objects are different.
     */
	bool date_interval::operator!=( const date_interval & other ) const
	{
		return value != other.value;
	}

    /** Determine if two date_interval objects are equal.
     */
	bool date_interval::operator==( const date_interval & other ) const
	{
		return value == other.value;
	}

//-----------------------------------------------------------------------------

    /** Create a date_exception object with the specified text.
     *  date_exception is derived from std::exception; this message will be 
     *  reported by calling the what() method.
     */
	date_exception::date_exception( const char * const msg )
		: std::invalid_argument( msg )
	{
	}

//-----------------------------------------------------------------------------

    /** Default construct a simple_date.
     *  The default date is invalid, but extra error checking needs to be
     *  implemented.
     */
	simple_date::simple_date()
		: julian( -1 )
	{
	}

//-----------------------------------------------------------------------------

    /** Create a simple_date object from its constituent parts.
     *  This is a "whole value" constructor (see 
     *  http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedIdioms.pdf)
     *  to avoid any ambiguity about the order of arguments. 
     *
     *  \throw date_exception If the date is invalid
     */
	simple_date::simple_date( year y, month m, int day )
	{
		validate( y, m, day );

		int yr = y.value;
		int mth = int( m ) + 1;

		if( mth < 3 )
		{
			--yr;
			mth += 12;
		}
		
		int a = yr / 100;
		int b = a / 4;
		int c = 2 - a + b;
		int d = day;
		int e = static_cast< int >( 365.25 * ( yr + 4716.0 ) );
		int f = static_cast< int >( 30.6001 * ( mth + 1 ) );

		julian = c + d + e + f - 1524.5;
	}

//-----------------------------------------------------------------------------

    /** Access the year part of the date.
     *  \sa year
     */

    /* This could be improved by storing the year part having either obtained
     * it in a constructor, or calculated it once.
     */
	year simple_date::get_year() const
	{
		int y, m, d;
		convert( julian, y, m, d );
		return year( y );
	}

//-----------------------------------------------------------------------------
	
    /** Access the month part of the date.
     *  \sa month
     */

    /* This could be improved by storing the month part having either obtained
     * it in a constructor, or calculated it once.
     */
	month simple_date::get_month() const
	{
		int y, m, d;
		convert( julian, y, m, d );
		return static_cast< month >( m );
	}

//-----------------------------------------------------------------------------
	
    /** Access the day part of the date.
     */

    /* This could be improved by storing the day part having either obtained
     * it in a constructor, or calculated it once.
     */
	int simple_date::get_day() const
	{
		int y, m, d;
		convert( julian, y, m, d );
		return d;
	}

//-----------------------------------------------------------------------------

    /** Calculate the day of the week represented by the date.
     *  \sa day_of_week
     */
	day_of_week simple_date::get_day_of_week() const
	{
		return static_cast< day_of_week >( static_cast< int >( julian + 2 ) % 7 );
	}

//-----------------------------------------------------------------------------

    /** Determine if "this" date is before the other date.
     */
	bool simple_date::operator<( const simple_date & other ) const
	{
		return julian < other.julian;
	}

//-----------------------------------------------------------------------------

    /** Determine if "this" date is not equal to the other date.
     */
	bool simple_date::operator!=( const simple_date & other ) const
	{
		return julian != other.julian;
	}

//-----------------------------------------------------------------------------

    /** Calculate the difference between two dates.
     *  The interval is negative if "this" is less-than (before) the other
     *  date.
     *  \sa date_interval
     */
	date_interval simple_date::operator-( const simple_date & other )
	{
		return julian - other.julian;
	}

//-----------------------------------------------------------------------------
	
    /** Subtract the supplied date_interval from "this" date and store the 
     *  result.
     *  \sa date_interval
     */
	simple_date & simple_date::operator-=( const date_interval & other )
	{
		julian -= other.days();
		return *this;
	}

//-----------------------------------------------------------------------------
	
    /** Add the suppied date_interval to "this" date and store the result.
     *  \sa date_interval
     */
	simple_date & simple_date::operator+=( const date_interval & other )
	{
		julian += other.days();
		return *this;
	}

//-----------------------------------------------------------------------------
	
	bool operator==( const simple_date & left, const simple_date & right )
	{
		return !( left != right );
	}

	bool operator>( const simple_date & left, const simple_date & right )
	{
		return ( left != right ) && !( left < right );
	}

	int to_iso_date( const simple_date & date )
	{
		return date.get_year().value * 10000 + ( date.get_month() + 1 ) * 100 + date.get_day();
	}

	bool is_leap_year( year y )
	{
		return y.value % 100 == 0 ? y.value % 400 == 0 : y.value % 4 == 0;
	}

//-----------------------------------------------------------------------------

	void convert( double jul, int & y, int & m, int & d )
	{
		int z = static_cast< int >( jul + 0.5 );
		int w = static_cast< int >( ( z - 1867216.25 ) / 36524.25 );
		int x = w / 4;
		int a = z + 1 + w - x;
		int b = a + 1524;
		int c = static_cast< int >( ( b - 122.1 ) / 365.25 );
		int d1 = static_cast< int >( 365.25 * c );
		int e = static_cast< int >( ( b - d1 ) / 30.6001 );
		int f = static_cast< int >( 30.6001 * e );

		d = b - d1 - f;
		m = e - 1;
		if( m > 12 )
		{
			m -= 12;
		}

		if( m < 3 )
		{
			y = c - 4715;
		}
		else
		{
			y = c - 4716;
		}
		--m;
	}

//-----------------------------------------------------------------------------

	void validate( year y, month m, int day )
	{
		if( y.value < 1582 )
		{
			throw date_exception( "Year too early - epoch error" );
		}
		if( m < 0 || m > 11 )
		{
			throw date_exception( "Invalid month" );
		}
		
		int upper = 31;
		switch( m )
		{
		case feb:
			upper = is_leap_year( y ) ? 29 : 28;
			break;

		case apr:
		case jun:
		case sep:		
		case nov:
			upper = 30;
			break;

		case jan:
		case mar:
		case may:
		case jul:
		case aug:
		case oct:
		case dec:
		default:
			break;
		}
		if( day > upper || day < 1 )
		{
			throw date_exception( "Day in month out of range" );
		}
	}

//-----------------------------------------------------------------------------

/** \fn         bool operator==( const simple_date & l, const simple_date & r )
 *  \brief      Determine if two simple_date objects are equivalent.
 */
/** \fn         bool operator>(  const simple_date & l, const simple_date & r )
 *  \brief      Determine if the left-hand argument l is larger than the 
 *              right-hand argument r.
 */
/** \fn         void convert( double jul, int & year, int & month, int & day )
 *  \brief      Convert a julian number representing a date in years following 
 *              1582 to its gregorian representation
 */
/** \fn         void validate( year y, month m, int day )
 *  \brief      Validate a gregorian date.
 */
/** \fn         int to_iso_date( const simple_date & d )
 *  \brief      Represent a simple_date object in simple ISO format (yyyymmdd)
 */
/** \fn         bool is_leap_year( year y )
 *  \brief      Determine if a given year is a leap year. Works for years that
 *              also work with simple_date
 */
/** \var        year::value
 *  \brief      Public access to the value used to store the year.
 */

}// utility
//-----------------------------------------------------------------------------
