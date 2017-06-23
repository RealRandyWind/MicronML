// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MICRONML_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MICRONML_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MICRONML_EXPORTS
#define MICRONML_API __declspec(dllexport)
#else
#define MICRONML_API __declspec(dllimport)
#endif

// This class is exported from the MicronML.dll
class MICRONML_API CMicronML {
public:
	CMicronML(void);
	// TODO: add your methods here.
};

extern MICRONML_API int nMicronML;

MICRONML_API int fnMicronML(void);
