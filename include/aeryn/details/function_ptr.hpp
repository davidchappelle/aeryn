
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

/** \file function_ptr.hpp
 *  \brief function_ptr implementation.
 */	

#ifndef AERYN_HENNEY_FUNCTION_PTR_HPP
#define AERYN_HENNEY_FUNCTION_PTR_HPP

#include <string>
#include <sstream>

namespace Aeryn
{
	namespace Henney
	{
		/**	\brief A generic function pointer that will take functions of any return type
		 *	and up to one argument of any type.
		 *	\author Kevlin Henney & Paul Grenyer
		 *
		 *	@see unary_adaptor
		 *	@see nullary_adaptor
		 */
		class function_ptr
		{
		public:
			/**	\brief Default constructor. */
			function_ptr()
				: body(0)
			{
			}

			/**	\brief Constructor for functions without any arguments. 
			 *	\param function The address of the function to be called.
			 */
			template<typename nullary_function>
			function_ptr(nullary_function function )
				: body(new nullary_adaptor<nullary_function >(function) )
			{
			}

			/**	\brief Constructor for functions with a single argument.
			  *	\param function The address of the function to be called.
			  *	\param param The object to be passed to the function when it is called.
			  *	The object is passed by copy.
			  */
			template<typename unary_function, typename param_type>
				function_ptr(unary_function function,  param_type param )
				: body(new unary_adaptor<unary_function, param_type>(function,param))
			{
			}

			/**	\brief Copy constructor. */
			function_ptr(const function_ptr &other)
				: body(other.body ? other.body->clone() : 0)
			{
			}

			/**	\brief Destructor. */
			~function_ptr()
			{
				delete body;
			}

			/**	\brief Copy-assignment operator. */
			function_ptr &operator=(const function_ptr &rhs)
			{
				callable *old_body = body;
				body = rhs.body ? rhs.body->clone() : 0;
				delete old_body;
				return *this;
			}

			/**	\brief Used to call the function. */
			void operator()() const
			{
				if(body)
					body->call();
			}

			/**	\brief Pointer operator. */
			function_ptr &operator*()
			{
				return *this;
			}

			/**	\brief Const pointer operator. */
			const function_ptr &operator*() const
			{
				return *this;
			}

			bool has_context() const
			{
				return body->has_context();
			}

			std::string context_string() const
			{
				return body->context_string();
			}

		private:
			/**	\brief Interface for function holder. 
			 *	
			 *	Interface for function holder.
			 *
			 *	@see function_ptr
			 */
			class callable
			{
			public:
				/**	\brief Destructor. */
				virtual ~callable()
				{
				}

				/**	\brief Used to make a copy of the function holder. */
				virtual callable *clone() const = 0;

				/**	\brief Used to call the function. */
				virtual void call() = 0;

				virtual bool has_context() const = 0;

				virtual std::string context_string() const = 0;
			};

			/**	\brief A function adapter for functions taking a single parameter of any type.
			 *	\author Kevlin Henney & Paul Grenyer
			 *	
			 *	@see function_ptr
			 */
			template<typename unary_function, typename param_type>
			class unary_adaptor : public callable
			{
			public:
				/**	\brief Constructor
				 *
				 *	\param function Pointer to the function.
				 *	\param param Parameter to be passed to the function when called. Must be copyable.
				 */
				unary_adaptor(unary_function function, param_type p)
					: adaptee(function), param( p )
				{
				}

				/**	\brief Allows adapter to be copied.
				 *
				 *	\return A copy of the adapter.
				 */
				virtual callable *clone() const
				{
					return new unary_adaptor<unary_function, param_type>(adaptee,param);
				}

				/**	\brief Calls the function.
				 *
				 *	The parameter passed into the constructor is passed to the function when it is called.
				 */
				virtual void call( )
				{
					adaptee( param );
				}

				virtual bool has_context() const
				{
					return true;
				}

				virtual std::string context_string() const
				{
					std::stringstream str;
					str << param;
					return str.str();
				}

			private:
				/**	\brief A pointer to the function to be called. */
				unary_function adaptee;

				/**	\brief The parameter that is passed to the function when it is called. */
				param_type param;
			};

			/**	\brief A function adapter for functions with no parameters.
			 *	\author Kevlin Henney & Paul Grenyer
			 *	
			 *	@see function_ptr
			 */
			template<typename nullary_function>
			class nullary_adaptor : public callable
			{
			public:
				/**	\brief Constructor
				 *
				 *	\param function Pointer to the function.
				 */
				nullary_adaptor(nullary_function function)
					: adaptee(function)
				{
				}

				/**	\brief Allows adapter to be copied.
				 *
				 *	\return A copy of the adapter.
				 */
				virtual callable *clone() const
				{
					return new nullary_adaptor<nullary_function>( adaptee );
				}

				/**	\brief Calls the function. */
				virtual void call( )
				{
					adaptee();
				}

				virtual bool has_context() const
				{
					return false;
				}

				virtual std::string context_string() const
				{
					return "";
				}

			private:				
				/**	\brief A pointer to the function to be called. */
				nullary_function adaptee;				
			};

			/**	Pointer to function holder. */
			callable *body;
		};
	}

	/** \brief Renames function_ptr and brings it into Aeryn namespace. */
	typedef Henney::function_ptr FunctionPtr;
}

#endif // AERYN_HENNEY_FUNCTION_PTR_HPP
