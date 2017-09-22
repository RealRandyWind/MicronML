#include "stdafx.h"
#include "ExceptionManager.h"

#define MicronML_Exception_ExitCode (unsigned(Exception.Type) | unsigned(Exception.Code) << 16)
#define MicronML_Exception_Message "  Exception %u.%u\n    at %s(%i)\n    function '%s'\n    catched by '%s';\n"

using namespace MicronML;

CExceptionManager* CExceptionManager::Instance = nullptr;

CExceptionManager::CExceptionManager()
{
}

CExceptionManager::~CExceptionManager()
{
}

CExceptionManager* CExceptionManager::GetInstance()
{
	if (!Instance) { Instance = new CExceptionManager(); }
	return Instance;
}

void CExceptionManager::UseDefaultCatch()
{
	CExceptionManager* Manager = GetInstance();
	Manager->OnExceptionEvent.Add(FOnExceptionEvent::Pack<CExceptionManager, &CExceptionManager::Catch>(Manager));
}

void CExceptionManager::Throw(FException Exception)
{
	GetInstance()->OnExceptionEvent.Signal(Exception);
}

void CExceptionManager::Catch(const FException Exception)
{
	printf_s(MicronML_Exception_Message,
		Exception.Type, Exception.Code,
		__FILE__, __LINE__,
		Exception.FunctionSignature, __FUNCDNAME__
	);
	if (Exception.Type == EExceptionType::Error)
	{
		exit(MicronML_Exception_ExitCode);
	}
}
