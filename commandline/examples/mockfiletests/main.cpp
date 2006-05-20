
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

/** \file examples\mockfiletests\main.cpp
 *  \brief The beginnings of a mock objects file accessor example.
 */	

#include <aeryn/is_equal.hpp>
#include <aeryn/test_runner.hpp>
#include <aeryn/use_name.hpp>
#include <aeryn/is_true.hpp>
#include <iostream>
#include <string>
#include <vector>

/**	\brief File accessor interface. */
class IFile
{
protected:
	/**	\brief Protected default constructor to force inheritance. */
	IFile()
	{
	}

public:
	/**	\brief Destructor. */
	virtual ~IFile() = 0
	{
	}

	/**	\brief Opens file.
	 *
	 *	\param filename Name of file to open.
	 *	\return true if the file is successfully opened, otherwise false.
	 */
	virtual bool Open( const std::string& filename ) = 0;

	/**	\brief Closes an open file. */
	virtual void Close() = 0;

	/**	\brief Reads a line from the file.
	 *
	 *	\return A std::string containing the line from the file.
	 */
	virtual std::string Read() = 0;

};

/**	\brief Real implementation of IFile interface. */
class File : public IFile
{
private:
	// ...

public:
	bool Open( const std::string& filename )
	{
		// Real code which opens a file.
		return true;
	}

	void Close()
	{
		// Real code which closes the file.
	}

	std::string Read()
	{
		// Real code which reads a line from th file.
		return "";
	}
};

/**	\brief Mock implementation of IFile interface. */
class MockFile : public IFile
{
public:
	/**	\brief Type of container for storing mock file lines. */
	typedef std::vector< std::string > LineCont;

	/**	\brief Constructor.
	 *
	 *	\param lines Mock file lines.
	 */
	MockFile( const LineCont lines )
		: line_( 0 ), lines_( lines )
	{
	}
	
	bool Open( const std::string& filename )
	{
		line_ = 0;
		return true;
	}

	void Close()
	{}

	std::string Read()
	{
		std::string result = lines_[ line_ ];
		++line_;
		return result;
	}

private:
	/**	\brief Current file line. */
	int line_;

	/**	\brief Mock file lines. */
	const LineCont lines_;
};

/**	\brief MockFile tests. */
void TestMockFile()
{
	MockFile::LineCont lines;
	lines.push_back( "Line 1" );
	lines.push_back( "Line 2" );
	lines.push_back( "Line 3" );
	lines.push_back( "Line 4" );

	MockFile mockFile( lines );
	IS_TRUE( mockFile.Open( "myfile.txt") );
	IS_EQUAL( lines[0], mockFile.Read() );
	IS_EQUAL( lines[1], mockFile.Read() );
	IS_EQUAL( lines[2], mockFile.Read() );
	IS_EQUAL( lines[3], mockFile.Read() );
}

/**	\brief Runs mock file tests. */
int main()
{
	using namespace Aeryn;
	TestRunner testRunner;
	testRunner.Add( USE_NAME( TestCase( USE_NAME( TestMockFile ) ) ) );
	return testRunner.Run();
}


