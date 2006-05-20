
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

/** \file incarnate.hpp
 *  \brief Definition of incarnate.
 *
 *	Incarnate was written by Kevlin Henney (http://www.curbralan.com/).
 */	

#ifndef AERYN_HENNEY_INCARNATE_HPP
#define AERYN_HENNEY_INCARNATE_HPP

namespace Aeryn
{
	namespace Henney
	{
		/**	\brief Delays creation of an object and calls a function which takes no parameters. 
		 *	\author Kevlin Henney
		 */
		template<typename target_type>
		class nullary_incarnate_function
		{
		public:
			/**	\brief Constructor
			 *
			 *	\param function Member function pointer to the member function that will
			 *	be called when the object is created.
			 */
			nullary_incarnate_function(void (target_type::*function)())
				: function(function)
			{
			}

			/**	\brief Creates object and calls specified function. */
			void operator()() const
			{
				target_type target;
				(target.*function)();
			}

		private:
			/**	\brief Holder for member function pointer. */
			void (target_type::*function)();			
		};

		/**	\brief Delays creation of an object and calls a function which takes a single parameter. 
		 *	\author Kevlin Henney & Paul Grenyer
		 */
		template<typename target_type, typename param_type>
		class unary_incarnate_function
		{
		public:
			/**	\brief Constructor
			 *
			 *	\param function Member function pointer to the member function that will
			 *	be called when the object is created.
			 *	\param param The parameter that will be passed to the member function when
			 *	it is called.
			 */
			unary_incarnate_function(void (target_type::*function)(), param_type param)
				: function(function), param(param)
			{
			}

			/**	\brief Creates object and calls specified function with specified parameter. */
			void operator()() const
			{
				target_type target( param );
				(target.*function)();
			}

		private:
			/**	\brief Holder for member function pointer. */
			void (target_type::*function)();

			/**	\brief Holder for parameter passed to member function. */
			param_type param;
		};

		/**	\brief Incarnate helper function.
		 *
		 *	This function simplifies the use of nullary_incarnate_function.
		 *
		 *	\param function Member function pointer to the member function that will
		 *	be called when the object is created.
		 */
		template<typename target_type>
		nullary_incarnate_function<target_type> incarnate(
		void (target_type::*function)())
		{
			return nullary_incarnate_function<target_type>(function);
		}

		/**	\brief Incarnate helper function.
		 *
		 *	This function simplifies the use of unary_incarnate_function.
		 *
		 *	\param function Member function pointer to the member function that will
		 *	be called when the object is created.
		 *	\param param The parameter that will be passed to the member function when
		 *	it is called.
		 */
		template<typename target_type, typename param_type>
		unary_incarnate_function<target_type,param_type> incarnate(
		void (target_type::*function)(), param_type param)
		{
			return unary_incarnate_function<target_type,param_type>(function,param);
		}
	}	

	/**	\brief Incarnate helper function.
	 *
	 *	Brings Henney::incarnate into  Aeryn namespace.
	 *
	 *	\param function Member function pointer to the member function that will
	 *	be called when the object is created.
	 */
	template<typename target_type>
	Henney::nullary_incarnate_function<target_type> Incarnate
	(
		void (target_type::*function)()
	)
	{
		return Henney::incarnate<target_type>(function);
	}

	/**	\brief Incarnate helper function.
	 *
	 *	Brings Henney::incarnate into  Aeryn namespace.
	 *
	 *	\param function Member function pointer to the member function that will
	 *	be called when the object is created.
	 *	\param param The parameter that will be passed to the member function when
	 *	it is called.
	 */
	template<typename target_type, typename param_type>
	Henney::unary_incarnate_function<target_type,param_type> Incarnate
	(
		void (target_type::*function)(),
		param_type param
	)
	{
		return Henney::incarnate<target_type,param_type>(function,param);
	}

}

#endif // AERYN_HENNEY_INCARNATE_HPP
