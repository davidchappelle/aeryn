// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TESTS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TESTS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TESTS_EXPORTS
#define TESTS_API __declspec(dllexport)
#else
#define TESTS_API __declspec(dllimport)
#endif

// This class is exported from the tests.dll
class TESTS_API Ctests {
public:
	Ctests(void);
	// TODO: add your methods here.
};

extern TESTS_API int ntests;

TESTS_API int fntests(void);
