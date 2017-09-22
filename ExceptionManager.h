#pragma once

#include "MicronML_Types.h"
#include "MicronML_Exceptions.h"
#include "MicronML_Events.h"

#define MicronML_Throw_Internal(Type, Code, OtherPointer) Throw({ Type, Code, __FUNCSIG__, OtherPointer })
#define MicronML_Throw(Type, Code, OtherPointer) MicronML::CExceptionManager::MicronML_Throw_Internal(Type, Code, OtherPointer)

#define MicronML_Throw_Warning(Code) MicronML_Throw(MicronML::EExceptionType::Warning, Code, nullptr)
#define MicronML_Throw_Error(Code) MicronML_Throw(MicronML::EExceptionType::Error, Code, nullptr)
#define MicronML_Throw_Success(Code) MicronML_Throw(MicronML::EExceptionType::Success, Code, nullptr)
#define MicronML_Throw_Log(Code) MicronML_Throw(MicronML::EExceptionType::Log, Code, nullptr)
#define MicronML_Throw_Info(Code) MicronML_Throw(MicronML::EExceptionType::Info, Code, nullptr)
#define MicronML_Throw_Debug(Code) MicronML_Throw(MicronML::EExceptionType::Debug, Code, nullptr)

#define MicronML_Throw_Unkown() MicronML_Throw(MicronML::EExceptionType::Unknown, MicronML::EExceptionCode::Unknown, nullptr)
#define MicronML_Throw_NotSupported() MicronML_Throw_Warning(MicronML::EExceptionCode::FunctionNotSuppored)
#define MicronML_Throw_Deprecated() MicronML_Throw_Warning(MicronML::EExceptionCode::FunctionDeprecated)

namespace MicronML
{
	class MICRONML_API CExceptionManager final
	{
	public:
		~CExceptionManager();
		static CExceptionManager* GetInstance();
		static void UseDefaultCatch();
		static void Throw(FException Exception);
		void Catch(const FException Exception);

		FOnExceptionEvent OnExceptionEvent;
	private:
		CExceptionManager();
		static CExceptionManager* Instance;
	};
}

