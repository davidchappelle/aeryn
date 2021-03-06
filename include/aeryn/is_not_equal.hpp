
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

/** \file is_not_equal.hpp
 *  \brief Definition of IS_NOT_EQUAL test condition macro and implementation function declaration and
 *	associated templates.
 */	

#ifndef AERYN_IS_NOT_EQUAL_HPP
#define AERYN_IS_NOT_EQUAL_HPP

#include <aeryn/test_failure.hpp>
#include <aeryn/details/is_streamable.hpp>
#include <aeryn/details/func_name.hpp>
#include <aeryn/details/print.hpp>
#include <sstream>

#ifdef  _MSC_VER
#pragma warning( disable : 4267 )
#endif

/**	\brief IS_NOT_EQUAL test condition macro.
*
*	<b>Failure condition:</b>	The IS_NOT_EQUAL test condition throws if the values held in lhs and 
*	rhs are equal. Eg:
*
*	IS_NOT_EQUAL( 42, 42  );
*
*	<b>Failure message:</b>	If the types of lhs and rhs are streamable a message detailing the failure 
*	is created. Eg:
*
*	Expected not to get '42'.
*
*	If the types are not streamable the test condition is used. Eg:
*
*	IS_NOT_EQUAL( 42, 42 );
* 
*	<b>Example:</b> <code>IS_NOT_EQUAL( lifeTheUniverseAndEverything, 43 );</code>
*/
#define IS_NOT_EQUAL( lhs, rhs ) ::Aeryn::IsNotEqual( lhs, rhs, #lhs, #rhs, __LINE__, __FILE__ )

namespace Aeryn
{
	namespace details
	{
		/**	\brief Print definition for IsNotEqual when using streamable types.
		 *
		 *	This Print template is used to make sure the correct error
		 *	message is given by the IsNotEqual function when the type being 
		 *	tested is streamable.
		 *
		 *	@see FuncName
		 *	@see IsStreamable
		 */
		template<>
		class Print< true, IsNotEqualFunc >
		{
		public:
			/**	\brief Formats the error message for the IsNotEqual function.
			 *
			 *	\param rhs The value on the right-hand-side of the IS_NOT_EQUAL macro.
			 */
			template< typename T, typename U >
			static std::string Out
			( 
				const T&, 
				const U& rhs,
				const char*, 
				const char*
			)
			{
				std::stringstream str;
				str << "Expected not to get '" << rhs << "'";
				return str.str();
			}
		};

		/**	\brief Print definition for IsNotEqual when using non-streamable types.
		 *
		 *	This Print template is used to make sure the correct error
		 *	message is given by the IsNotEqual function when the type being 
		 *	tested is <b>not</b> streamable.
		 *
		 *	@see FuncName
		 *	@see IsStreamable
		 */
		template<>
		class Print< false, IsNotEqualFunc >
		{
		public:
			/**	\brief Formats the error message for the IsNotEqual function.
			 *
			 *	\param lhscode The code on the left-hand-side of the IS_NOT_EQUAL macro.
			 *	\param rhscode The code on the right-hand-side of the IS_NOT_EQUAL macro.
			 */
			template< typename T, typename U >
			static std::string Out
			( 
				const T&, 
				const U&,
				const char* lhscode, 
				const char* rhscode
			)
			{
				std::stringstream str;
				str << "IS_NOT_EQUAL(" << lhscode << "," << rhscode << ")";
				return str.str();			
			}
		};
	}

	/**	\brief Determines if two objects of any type are <b>not</b> equal (!=). Throws if they are.
	 *
	 *	\param lhs Object 1.
	 *	\param rhs Object 2.
	 *	\param lhscode A textural representation of object 1.
	 *	\param rhscode A textural representation of object 2.
	 *	\param line The line from which IsNotEqual is being called.
	 *	\param file The file from which IsNotEqual is being called.
	 *	\throws TestFailure if object 1 and object 2 are equal.
	 */
	template< typename T, typename U>
	inline void IsNotEqual
	( 
		const T& lhs, 
		const U& rhs, 
		const char* lhscode, 
		const char* rhscode,
		unsigned long line, 
		const char* file 
	)
	{
		if ( !(lhs != rhs) )
		{
			using namespace details;
			using namespace Williams;				
			
#ifdef NO_OUTPUT_OPERATOR_DETECTION
			const bool isStreamable = false;
#else 
			const bool isStreamable = IsStreamable< T >::result && IsStreamable< U >::result;
#endif			
			throw TestFailure( Print< isStreamable, IsNotEqualFunc >::template Out< T, U >
							( lhs, rhs, lhscode, rhscode ), line, file );
		}
	}

	/**	\brief Determines if strings are <b>not</b> equal (!=). Throws if they are.
	 *
	 *	\param lhs String 1.
	 *	\param rhs String 2.
	 *	\param lhscode A textural representation of string 1.
	 *	\param rhscode A textural representation of string 2.
	 *	\param line The line from which IsNotEqual is being called.
	 *	\param file The file from which IsNotEqual is being called.
	 *	\throws TestFailure if string 1 and string 2 are equal.
	 */
	void IsNotEqual
	( 
		const char* lhs, 
		const char* rhs,
		const char* lhscode, 
		const char* rhscode,
		unsigned long line, 
		const char* file 
	);

}

#endif // AERYN_IS_NOT_EQUAL_HPP
