
#include "dll_path.h"

namespace Aeryn
{
	namespace DynamicLibrary
	{
		//////////////////////////////////////////////////////////////////////////
		namespace
		{
#ifdef _DEBUG
			const std::string dllName = "dynamiclibrarybin_debug.dll";
#else
			const std::string dllName = "dynamiclibrarybin.dll";
#endif
		}
	
		//////////////////////////////////////////////////////////////////////////
		std::string DllPath( const std::string& path )
		{
			return path + dllName;
		}
	}
}
