
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

/** \file is_streamable.hpp
 *  \brief Definition of IsStreamable.
 *
 *	IsStreamable was written by Anthony Williams (http://www.justsoftwaresolutions.co.uk).
 */	

#ifndef AERYN_WILLIAMS_IS_STREAMABLE_HPP
#define AERYN_WILLIAMS_IS_STREAMABLE_HPP

#include <ostream>

namespace Aeryn
{
	namespace Williams
	{
		/**	\brief StreamableResult is the return type of our operator<<
		 *	No real operator<< should return it
		 *
		 *	\author Anthony Williams
		 */
		struct StreamableResult
		{};

		/** \brief Generic is a type constructible from anything
		 *
		 * The ellipsis constructor pushes this to the bottom of any
		 * conversion list.
		 *
		 *	\author Anthony Williams
		 */
		struct Generic
		{
			Generic(...);
		};

		/**	\brief This is our operator<<
		 *	It will accept anything as either parameter.
		 * 
		 * The template parameter on the lhs, means the lhs is always an
		 * exact match.
		 *
		 * The Generic parameter on the rhs will accept anything, but the
		 * constructor requires an implicit conversion through an
		 * ellipsis, so ranks lowest of all options Finally, this is a
		 * template, so it ranks lower than a non-template.
		 *
		 *	\author Anthony Williams
		 */
		template<typename T>
			StreamableResult operator<<(T const& t,Generic const& u);

		/** \brief getT is a dummy function with no implementation that returns
		 * any type we specify
		 */	
		template<typename T>
			T getT();

		/**	\brief FalseType is a placeholder type used when the selected overload
		 *	indicates our test was false
		 */
		typedef char FalseType;

		/**	\brief TrueType is a placeholder type with a different size to
		 *	 FalseType, used when the selected overload indicates our test was true
		 */
		struct TrueType
		{
			char dummy[2];
		};

		/**	\brief IsStreamable is the public API here:
		 *  
		 *  IsStreamable<SomeType>::result is true if SomeType can be
		 *  streamed to an ostream using operator<<
		 * 
		 *  The operands to sizeof are not called, so getT() doesn't need
		 *  an implementation, and we don't need to impose any requirements
		 *  on T; we don't need any objects or means of creating them in
		 *  order to test the streamability of a type.
		 *  
		 *  Overload resolution rules mean that any real operator<< for T
		 *  takes precedence over our dummy operator<< above, but the
		 *  operator<< expression always evaluates to something (even if
		 *  it's our dummy operator<<)
		 * 
		 *  The overloads of testStreamable ensure that expressions that
		 *  resolve to our dummy operator<< are separated from those that
		 *  resolve to a "real" operator<< --- if our dummy operator<< is
		 *  required, then the type T does not have a "real" operator<<.
		 * 
		 *  The return types of the overloads have different sizes, so we
		 *  can then use sizeof() to determine which overload was called.
		 *
		 *	\author Anthony Williams
		 */		 
		template<typename T>
		struct IsStreamable
		{
			static FalseType testStreamable
				( const StreamableResult& );

			static TrueType testStreamable
				(...);

			static const bool result = 
				sizeof( testStreamable( getT< std::ostream& >() << getT< T const & >() ) ) ==
				sizeof( TrueType );
		};	
	}
}

#endif // AERYN_WILLIAMS_IS_STREAMABLE_HPP

