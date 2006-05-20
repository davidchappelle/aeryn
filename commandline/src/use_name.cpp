
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

/** \file use_name.cpp
 *  \brief USE_NAME formatting functions.
 */	

#include <aeryn/use_name.hpp>
#include <cctype>
#include <cassert>

namespace Aeryn
{
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		/**	\brief Remove Incarnate.
		 *
		 *	If found, removes "<code>Incarnate</code>" and associated parenthesis from supplied string.
		 *
		 *	\param name String to remove <code>Incarnate</code> from.
		 *	\return A copy of the string with <code>Incarnate</code> removed.
		 */
		std::string RemoveIncarnate
			( const std::string& name )
		{
			std::string result = name;
			std::string::size_type pos = result.find( "Incarnate(" );

			if ( pos != std::string::npos )
			{
				pos = result.find( "&", pos );	
				assert( pos != std::string::npos );
				result = result.substr( pos + 1 );

				pos = std::min( result.find( ")" ), result.find( "," ) );	
				assert( pos != std::string::npos );
				result.erase( pos );
			}
			
			return result;
		}

		/**	\brief Remove FunctionPtr.
		 *
		 *	If found, removes "<code>FunctionPtr</code>" and associated parenthesis from supplied string.
		 *
		 *	\param name String to remove <code>FunctionPtr</code> from.
		 *	\return A copy of the string with <code>FunctionPtr</code> removed.
		 */
		std::string RemoveFunctionPtr
			( const std::string& name )
		{
			const std::string funcPtr = "FunctionPtr(";
			
			std::string result = name;
			std::string::size_type pos = result.find( funcPtr );

			if ( pos != std::string::npos )
			{
				result = result.substr( funcPtr.length() );
				
				pos = std::min( result.find( ")" ), result.find( "," ) );	
				assert( pos != std::string::npos );
				result.erase( pos );
			}

			return result;
		}

		/**	\brief Removes "&"
		 *
		 *	If found, removes the first "&" found in the supplied string.
		 *
		 *	\param name String to remove the first "&" from.
		 *	\return A copy of the string with the first "&" removed.
		 */
		std::string RemoveAmp
			( const std::string& name )
		{
			std::string result = name;
			std::string::size_type pos = result.find( "&" );
			if ( pos != std::string::npos )
			{
				result.erase( pos, 1 );
			}
			return result;
		}


		/**	\brief Removes qualifier from fully qualified names.
		 *
		 *	If found, removes the qualifier from fully qualified names. For example MyClass::MyFunc becomes
		 *	MyFunc.
		 *
		 *	\param name String to remove the qualifier from.
		 *	\return A copy of the string with the qualifier removed.
		 */
		std::string RemoveQualifier
			( const std::string& name )
		{
			std::string result = name;
			std::string::size_type pos = result.find( "::" );

			if ( pos != std::string::npos )
			{
				result = result.substr( pos + 2 );
			}

			return result;
		}

		/**	\brief Title cases
		 *
		 *	Title cases the supplied string.
		 *
		 *	\param name String to be title cased.
		 *	\return A copy of the string title cased.
		 */
		std::string TitleCase
			( const std::string& name )
		{
			std::string result;
			for( std::string::size_type i = 0; i < name.length(); ++i )
			{
				if ( i == 0)
				{
					result += toupper( name[i] );
				}
				else
				{
					if ( std::isupper( name[ i ] ) )
					{
						result += ' ';
					}

					result += name[ i ];
				}
			}

			return result;
		}

		/**	\brief Strips leading and following spaces.
		 *
		 *	\param name String to have spaces removed from.
		 *	\return A copy of the string with leading and following spaces removed.
		 */
		std::string StripSpaces
			( const std::string& name )
		{
			std::string result = name;
			while( result[0] == ' ' )
			{
				result.erase( 0, 1 );
			}

			while( result[ result.length() - 1 ] == ' ' )
			{
				result.erase( result.length() - 1 );
			}

			return result;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	std::string FormatName
	( 
		const std::string& name 
	)
	{
		std::string result = RemoveIncarnate( name );
		result = RemoveFunctionPtr( result );
		result = RemoveAmp( result );
		result = RemoveQualifier( result );
		result = TitleCase( result );
		result = StripSpaces( result );
		return result;
	}
}

