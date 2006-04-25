
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

/** \file noncopyable.hpp
 *  \brief Noncopyalbe definition.
 */	

#ifndef AERYN_UTILS_NONCOPYABLE_HPP
#define AERYN_UTILS_NONCOPYABLE_HPP



namespace Aeryn
{
	namespace Utils
	{
		/**	\brief Inherit from this class to make the subclass non-copyable */
		class Noncopyable
		{
		protected:
			/** \brief Protected constructor to force inheritance. */
			Noncopyable
				()
			{
			}

			/** \brief Protected destructor to force inheritance. */
			~Noncopyable
				()
			{
			}

		private:
			/**	\brief Private copy constructor to prevent copying. */
			Noncopyable
				( const Noncopyable& );

			/**	\brief Private copy assignment operator to prevent copying. */
			Noncopyable& operator=
				( const Noncopyable& );			
		};

		//////////////////////////////////////////////////////////////////////////		
	}
}

#endif // AERYN_UTILS_NONCOPYABLE_HPP
