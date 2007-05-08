
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

/** \file is_not_equal_delta.hpp
 *  \brief Definition of IS_NOT_EQUAL_DELTA test condition macro and implementation function declaration and
 *	associated templates.
 */	

#ifndef AERYN_IS_NOT_EQUAL_DELTA_HPP
#define AERYN_IS_NOT_EQUAL_DELTA_HPP

#include <aeryn/test_failure.hpp>
#include <aeryn/details/is_streamable.hpp>
#include <aeryn/details/func_name.hpp>
#include <aeryn/details/print.hpp>
#include <sstream>

#ifdef  _MSC_VER
#pragma warning( disable : 4267 )
#endif

/**	\brief IS_NOT_EQUAL_DELTA test condition macro.
 *
 *	<b>Failure condition:</b>	The IS_NOT_EQUAL_DELTA test condition throws if the difference between the 
 *	values held in lhs and rhs are less than delta. Eg:
 *
 *	IS_NOT_EQUAL_DELTA( 4, 2, 3 );
 *
 *	<b>Failure message:</b>	If the types of lhs and rhs are streamable a message detailing the 
 *	failure is created. Eg:
 *
 *	The difference between '4' and '2' is less than '3'.
 *
 *	If the types are not streamable the test condition is used. Eg:
 *
 *	IS_NOT_EQUAL_DELTA( 4, 2, 3 );
 * 
 *	<b>Example:</b> <code>IS_NOT_EQUAL_DELTA( lifeTheUniverseAndEverything, 42.5, 2 );</code>
 */
#define IS_NOT_EQUAL_DELTA( lhs, rhs, delta ) ::Aeryn::IsNotEqualDelta( lhs, rhs, delta, #lhs, #rhs, #delta, __LINE__, __FILE__ )

namespace Aeryn
{
	namespace details
	{
		/**	\brief Print definition for IsNotEqualDelta when using streamable types.
		 *
		 *	This Print template is used to make sure the correct error
		 *	message is given by the IsNotEqualEqual function when the type being 
		 *	tested is streamable.
		 *
		 *	@see FuncName
		 *	@see IsStreamable
		 */
		template<>
		class Print< true, IsNotEqualDeltaFunc >
		{
		public:
			/**	\brief Formats the error message for the IsNotEqualDelta function.
			 *
			 *	\param lhs The value on the left-hand-side of the IS_NOT_EQUAL_DELTA macro.
			 *	\param rhs The value on the right-hand-side of the IS_NOT_EQUAL_DELTA macro.
			 *	\param delta The delta value.
			 */
			template< typename T >
			static std::string Out
			( 
				const T& lhs, 
				const T& rhs,
				const T& delta,
				const char*, 
				const char*,
				const char*
			)
			{
				std::stringstream str;
				str << "The difference between '" << lhs << "' and '" << rhs << "' is less than '" << delta << "'";
				return str.str();
			}
		};

		/**	\brief Print definition for IsEqualDelta when using non-streamable types.
		 *
		 *	This Print template is used to make sure the correct error
		 *	message is given by the IsNotEqualDelta function when the type being 
		 *	tested is <b>not</b> streamable.
		 *
		 *	@see FuncName
		 *	@see IsStreamable
		 */
		template<>
		class Print< false, IsNotEqualDeltaFunc >
		{
		public:
			/**	\brief Formats the error message for the IsNotEqualDelta function.
			 *
			 *	\param lhscode The code on the left-hand-side of the IS_NOT_EQUAL_DELTA macro.
			 *	\param rhscode The code on the right-hand-side of the IS_EQUAL_DELTA macro.
			 *	\param delta The delta value.
			 */
			template< typename T >
			static std::string Out
			( 
				const T&, 
				const T&,
				const T&,
				const char* lhscode, 
				const char* rhscode,
				const char* deltacode
			)
			{
				std::stringstream str;
				str << "IS_NOT_EQUAL_DELTA(" << lhscode << "," << rhscode << "," << deltacode << ")";
				return str.str();			
			}
		};

	}

	/**	\brief Determines if the difference between values is not within the specified limit (delta). Throws if they are.
	 *
	 *	\param lhs Object 1.
	 *	\param rhs Object 2.
	 *	\param delta The delta.
	 *	\param lhscode A textural representation of object 1.
	 *	\param rhscode A textural representation of object 2.
	 *	\param delta A textural representation of the delta.
	 *	\param line The line from which IsEqualDelta is being called.
	 *	\param file The file from which IsEqualDelta is being called.
	 *	\throws TestFailure if the differecne between object 1 and object 2 is greater than delta.
	 */
	template< typename T >
	inline void IsNotEqualDelta
	( 
		const T& lhs, 
		const T& rhs, 
		const T& delta,
		const char* lhscode, 
		const char* rhscode,
		const char* deltacode,
		unsigned long line, 
		const char* file 
	)
	{
		if (  ( rhs - lhs ) <= delta )
		{
			using namespace details;
			using namespace Williams;
			
#ifdef NO_OUTPUT_OPERATOR_DETECTION
			const bool isStreamable = false;
#else 
			const bool isStreamable = IsStreamable< T >::result;
#endif			
			throw TestFailure( Print< isStreamable, IsNotEqualDeltaFunc >::Out< T >
							( lhs, rhs, delta, lhscode, rhscode, deltacode ), line, file );
		}		
	}	
}

#endif // AERYN_IS_EQUAL_HPP
