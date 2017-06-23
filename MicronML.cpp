// MicronML.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MicronML.h"


// This is an example of an exported variable
MICRONML_API int nMicronML=0;

// This is an example of an exported function.
MICRONML_API int fnMicronML(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see MicronML.h for the class definition
CMicronML::CMicronML()
{
    return;
}
