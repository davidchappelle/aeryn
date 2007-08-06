
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

#ifndef UTILITY_UTILITY_SIMPLE_DATE_HEADER
#define UTILITY_UTILITY_SIMPLE_DATE_HEADER

/*
 *  RLW 2007-08-06 17:20
 *
 *  GCC on Solaris Sparc defines the symbol sun which interferes with this program's days of the week enum
 *  definition.  We take the view that sun should be #defined always for simplicity.
 */
#undef sun

//-----------------------------------------------------------------------------
/** \file       simple_date.hpp
 *  \brief		simple_date declaration.
 *  \author     Steve Love
 *  \date       May 2005
 */
//-----------------------------------------------------------------------------
/** \namespace  utility
 *  \brief      Collection of simple utility classes for use elsewhere
 *
 */
//-----------------------------------------------------------------------------
/** \class      utility::simple_date
 *  \brief      A simple date class to handle basic dates in Gregorian format
 *
 *  This date class is simple and cut down, allowing only the basic operations
 *	for general date usage. For a given date, accessors are provided for the
 *	year, month and day, and the day of the week. Additionally, two dates
 *	can be compared for equality/relational properties, the difference between
 *	2 dates can be obtained (see utility::date_interval), and times added to
 *	or subtracted from a date (see utility::date_interval).
 *	Attempting to create an invalid date (other than by the default 
 *	constructor) throws a date_exception (see utility::date_exception). This 
 *	catches common errors such as Feb 31st, or a year prior to 1582. This
 *	year is the first permitted year in this class, because julian numbering
 *	is used under the hood and only the simple calculations between julian
 *	and gregorian are implemented.
 *
 *	This date class is intended for non-localised programs, as it uses 
 *	English/Western terminology for dates (e.g. days of the week,
 *	months of the year).
 */


/**	\class		utility::date_interval
 *	\brief		A simple representation of the difference between two dates.
 *
 *	When one date (utility::simple_date) is subtracted from another the
 *	difference is represented by an interval. date_interval objects can be
 *	compared to each other to determine their (in)equality, and queried for
 *	the number of days they represent. The utility::simple_date class has no
 *	representation of time (fractional days) and so the date_interval's 
 *	granularity is a single day.
 */


/** \class      utility::date_exception
 *  \brief      Exception type thrown when attempting to create an invalid
 *              utility::simple_date
 *
 *  \sa         utility::simple_date
 */


/** \class      utility::year
 *  \brief      Primitive year type to take part in constructing 
 *              utility::simple_date objects
 *
 * The representation of a year is a simple structure so that c++'s type system
 * can take part in enforcing parameter ordering. For constructors this is 
 * the "WholePart" idiom, as described at 
 * http://www.two-sdg.demon.co.uk/curbralan/papers/ValuedIdioms.pdf
 *
 *  \sa         utility::month
 *  \sa         utility::simple_date
 */


/** \enum       utility::month
 *  \brief      Primitive month identifiers for the utility::simple_date class
 *  \sa         utility::year
 *  \sa         utlity::simple_date
 */


/** \enum       utlity::day_of_week
 *  \brief      Primitive identifiers for days of the week (in English)
 *  \sa         utility::simple_date
 */


//-----------------------------------------------------------------------------

#include <stdexcept>

//-----------------------------------------------------------------------------
namespace utility
{
	struct year
	{
		explicit year( int value );
		int value;
	};

	enum month
	{
		jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	enum day_of_week
	{
		sun, mon, tue, wed, thu, fri, sat
	};

	class date_interval;

	void convert( double jul, int & y, int & m, int & d );
	void validate( year y, month m, int d );

//-----------------------------------------------------------------------------

    class simple_date
    {
    public:
						simple_date();
						simple_date( year y, month m, int day );

		year			get_year() const;
		month			get_month() const;
		int				get_day() const;
		day_of_week		get_day_of_week() const;

		bool			operator<( const simple_date & other ) const;
		bool			operator!=( const simple_date & other ) const;

		date_interval	operator-( const simple_date & other );

		simple_date &	operator-=( const date_interval & difference );
		simple_date &	operator+=( const date_interval & difference );

    private:
		double			julian;
    };

//-----------------------------------------------------------------------------

	class date_interval
	{
	public:
		date_interval( double diff );
		int days() const;
		bool operator==( const date_interval & other ) const;
		bool operator!=( const date_interval & other ) const;		

	private:
		double value;
	};

//-----------------------------------------------------------------------------

	class date_exception : public std::invalid_argument
	{
	public:
		date_exception( const char * const msg );
	};

//-----------------------------------------------------------------------------

	bool operator==( const simple_date & left, const simple_date & right );

	bool operator>( const simple_date & left, const simple_date & right );

	int to_iso_date( const simple_date & date );

	bool is_leap_year( year y );

//-----------------------------------------------------------------------------
}// utility
//-----------------------------------------------------------------------------

#endif // UTILITY_UTILITY_SIMPLE_DATE_HEADER
