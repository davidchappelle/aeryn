
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

/** \file platform_report_output.hpp
 *  \brief Classes used to format report output for particular compilers.
 */	

#ifndef AERYN_PLATFORM_REPORT_OUTPUT_HPP
#define AERYN_PLATFORM_REPORT_OUTPUT_HPP

#include <aeryn/platform.hpp>
#include <aeryn/test_failure.hpp>
#include <sstream>

namespace Aeryn
{
	/**	\brief Default report failure formatter.
	 *
	 *	Compatible with GCC, KDevelop etc.
	 */
	template< Compiler T > 
	class FormatFailure
	{
	public:
		/**	\brief Formats failure information.
		 *
		 *	\param msg The failure message.
		 *	\param line The line the failure appeared on.
		 *	\param file The file the failure occurred in.
		 */
		static std::string Out
			( const std::string& msg, 
			  unsigned long line,
			  const char* file )
		{
			std::stringstream str;
			str << file << ":" << line << ": " << msg << "\n";
			return str.str();
		}

		/**	\brief Formats failure information.
		 *
		 *	\param failure The failure information.
		 */
		static std::string Out
			( const TestFailure& failure )
		{
			return Out( failure.Failure(), failure.Line(), failure.File().c_str() );
		}
	};

	/**	\brief Microsoft Visual C++ report failure formatter. */
	template<> 
	class FormatFailure< MSVC >
	{
	public:
		/**	\brief Formats failure information.
		 *
		 *	\param msg The failure message.
		 *	\param line The line the failure appeared on.
		 *	\param file The file the failure occurred in.
		 */
		static std::string Out
			( const std::string& msg, 
			  unsigned long line,
			  const char* file )
		{
			std::stringstream str;
			str << file << "(" << static_cast< unsigned long>( line ) << "): " << msg << "\n";

			return str.str();
		}

		/**	\brief Formats failure information.
		 *
		 *	\param failure The failure information.
		 */
		static std::string Out
			( const TestFailure& failure )
		{
			return Out( failure.Failure(), failure.Line(), failure.File().c_str() );
		}
	};
}

#endif // AERYN_PLATFORM_REPORT_OUTPUT_HPP
