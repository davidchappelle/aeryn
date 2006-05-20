
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

/** \file simple_calc.cpp
 *  \brief SimpleCalc definition.
 */	

#include "simple_calc.hpp"

namespace Aeryn
{
	double SimpleCalc::Add( double lhs, double rhs )
	{
		return lhs + rhs;
	}

	double SimpleCalc::Subtract( double lhs, double rhs )
	{
		return lhs - rhs;
	}

	double SimpleCalc::Multiply( double lhs, double rhs )
	{
		return lhs * rhs;
	}

	double SimpleCalc::Divide( double lhs, double rhs )
	{
		double result = 0;
		
		if ( rhs != 0 )
		{
			result = lhs / rhs;
		}
		else
		{
			throw DivideByZero();
		}

		return result;
	}
}
