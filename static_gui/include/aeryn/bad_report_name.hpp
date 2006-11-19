
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

/** \file bad_report_name.hpp
 *  \brief BadReportName declaration.
 */	

#ifndef AERYN_BAD_REPORT_NAME_HPP
#define AERYN_BAD_REPORT_NAME_HPP

#include <aeryn/exception.hpp>

namespace Aeryn
{
	/**	\brief Thrown if an invalid report name is specified. */
	class BadReportName : public Exception
	{
	public:
		/** \brief Constructor
		 *
		 *	\brief name The name of the report specified.
		 */
		explicit BadReportName
			( const std::string& name );
	};
}

#endif // AERYN_BAD_REPORT_NAME_HPP
