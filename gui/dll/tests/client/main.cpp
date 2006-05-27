
#include <iostream>
#include <windows.h>
#include <string>
#include <exception>
#include <cassert>

class DllException : public std::exception
{
private:
	static std::string GetMessage()
	{
		std::string result;
		
		LPVOID lpMsgBuf;
		if (FormatMessage(	FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL ))
		{
			result = (LPCTSTR)lpMsgBuf;

			// Free the buffer.
			LocalFree( lpMsgBuf );
		}

		return result;
	}

public:
	DllException()
		: std::exception( GetMessage().c_str() )
	{		
	}	
};

class DllLoader
{
private:
	HINSTANCE pDll_;

public:
	DllLoader( const std::string& path )
		: pDll_( LoadLibrary( path.c_str() ) )
	{
		if ( !pDll_ )
		{
			throw std::exception( "failed to laod Dll" );
		}
	}

	~DllLoader()
	{
		FreeLibrary( pDll_ );
	}

	unsigned long TestCount() const
	{
		unsigned long result = 0;

		FARPROC fn = GetProcAddress( pDll_, "TestCount" );
		if ( !fn )
		{
			throw DllException();
		}

		return fn();
	}
};

int main( int argc, char* argv[] )
{
	try
	{
		DllLoader dll( argv[1] );
		assert( dll.TestCount() != 0 );
		std::cout << "Test count: " << dll.TestCount() << "\n";
	}
	catch( const std::exception& e )
	{
		std::cout << e.what() << "\n";
	}

	return 0;
}
