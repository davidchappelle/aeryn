
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

/** \file comnand_line_parser.hpp
 *  \brief CommandLineParser declaration.
 */	

#ifndef AERYN_COMMAND_LINE_PARSER_HPP
#define AERYN_COMMAND_LINE_PARSER_HPP

#include <string>
#include <vector>

namespace Aeryn
{
	/**	\brief CommandLineParser tests 
	 *
	 *	Reads test names, test set names and a report name from the command line.
	 *
	 *	Test names are preceded by -t.
	 *	Test set names are preceded by -ts.
	 *	Reports are preceded by -4.
	 *
	 *	Example: -t "test 1" -ts "Test set 1" -r minimal
	 */
	class CommandLineParser
	{
	private:
		/**	\brief String store type. */
		typedef std::vector< std::string > StringStore;

		/**	Command with which the program is invoked. */
		std::string commandLine_;

		/**	Name of report to use */
		std::string report_;

		/** A store for test names. */
		StringStore tests_;

		/** A store for test set names. */
		StringStore testSets_;

	public:
		/**	\brief String store const iterator. */
		typedef StringStore::const_iterator ConstItr;

		/**	\brief String store size type. */
		typedef StringStore::size_type SizeType;

		/**	\brief Constructor
		 *	
		 *	\param argc An integer that contains the count of arguments that follow in argv. 
		 *	The argc parameter is always greater than or equal to 1. argv 
		 *
		 *	\param argv An array of null-terminated strings representing command-line arguments entered by the 
		 *	user of the program. By convention, argv[0] is the command with which the program is invoked, 
		 *	argv[1] is the first command-line argument, and so on, until argv[argc], which is always NULL. 
		 *	See Customizing Command Line Processing for information on suppressing command-line processing. 
		 *	The first command-line argument is always argv[1] and the last one is argv[argc – 1]. 
		 */
		CommandLineParser
			( int argc, char *argv[ ] );

		/**	\brief Returns command with which the program is invoked.
		 *
		 *	\return The command with which the program is invoked.
		 */
		std::string CommandLine
			() const;

		/**	\brief Returns the report specified on the command line, if any. 
		 *
		 *	\return The report specified on the command line, if any.
		 */
		std::string Report
			() const;

		/**	\brief Returns the number of tests.
		 *
		 *	\return The number of tests read from the command line.
		 */
		SizeType TestCount
			() const;

		/**	\brief Returns the begin iterator for the list of tests.
		 *
		 *	\return The begin iterator for the list of tests read from the command line.
		 */
		ConstItr TestBegin
			() const;

		/**	\brief Returns the end iterator for the list of tests.
		 *
		 *	\return The end iterator for the list of tests read from the command line.
		 */
		ConstItr TestEnd
			() const;

		/**	\brief Returns the number of tests sets.
		 *
		 *	\return The number of test sets read from the command line.
		 */
		SizeType TestSetCount
			() const;

		/**	\brief Returns the begin iterator for the list of test sets.
		 *
		 *	\return The begin iterator for the list of test sets read from the command line.
		 */
		ConstItr TestSetBegin
			() const;

		/**	\brief Returns the end iterator for the list of test sets.
		 *
		 *	\return The end iterator for the list of test sets read from the command line.
		 */
		ConstItr TestSetEnd
			() const;

	private:
		/** \brief Extracts the first argument from the command line.
		 *
		 *	\param argc An integer that contains the count of arguments that follow in argv. 
		 *
		 *	\param argv An array of null-terminated strings representing command-line arguments entered by the 
		 *	user of the program.
		 *
		 *	\return first argument from the command line.
		 */
		std::string ExtactCommandLine
			( int argc, char *argv[ ] ) const;

		/**	\brief Gets the next param from the command line.
		 *
		 *	Gets the next parameter from the commanline, if there is one, and increments
		 *	the counter passed in.
		 *
		 *	\param i The current counter.
		 *
		 *	\param argc An integer that contains the count of arguments that follow in argv. 
		 *
		 *	\param argv An array of null-terminated strings representing command-line arguments entered by the 
		 *	user of the program.
		 *
		 *	\param param Where to put the next parameter.
		 *
		 *	\return True if there is another parameter, otherwise false.
		 */
		bool GetNextParam
			( int& i, int argc, char *argv[ ], std::string& param );

	};
}

#endif // AERYN_COMMAND_LINE_PARSER_HPP
