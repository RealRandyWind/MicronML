#include "stdafx.h"
#include "IOManager.h"

using namespace MicronML;

CIOManager* CIOManager::Instance = nullptr;

CIOManager::CIOManager()
{
}


CIOManager::~CIOManager()
{
}

CIOManager* CIOManager::GetInstance()
{
	if (!Instance) { Instance = new CIOManager(); }
	return Instance;
}
