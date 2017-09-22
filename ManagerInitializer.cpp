#include "stdafx.h"
#include "ManagerInitializer.h"

using namespace MicronML;

CManagerInitializer::CManagerInitializer(pointer_t What, bool_t (*OnInitialize)(), bool_t (*OnTerminate)())
{
	Subject = What;
	Initialize = OnInitialize;
	Terminate = OnTerminate;
	bInitialized = OnInitialize();
	bTerminated = !bInitialized;
}

CManagerInitializer::~CManagerInitializer()
{
	bTerminated = Terminate();
	bInitialized = !bTerminated;
}

bool_t MicronML::CManagerInitializer::IsInitialized()
{
	return bInitialized;
}
