#include "stdafx.h"
#include "Result.h"

using namespace MicronML;

CManagerInitializer* CResult::Initializer = new CManagerInitializer(nullptr, Initialize, Terminate);
result_id CResult::InstanceIDCounter = MicronML_One;
CResult::FInstanceMap CResult::InstanceMap = { { MicronML_None, nullptr } };

CResult::CResult(FResultParameters Parameters)
{
	ID = MicronML_None;
	Raw = new FResult();
	OnMicronEvent = new FOnMicronEvent();
}

CResult::~CResult()
{
	delete Raw;
	delete OnMicronEvent;
}

result_id CResult::GetID()
{
	return ID;
}

FResult* CResult::GetRaw()
{
	if (ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::NoneResult); return nullptr; }
	return Raw;
}

bool_t CResult::Initialize()
{
	return true;
}

bool_t CResult::Terminate()
{
	return true;
}

CResult* CResult::Make(FResultParameters Parameters)
{
	CResult* Result;

	Result = new CResult(Parameters);
	Result->ID = InstanceIDCounter++;
	InstanceMap[Result->ID] = Result;
	return Result;
}

CResult* CResult::Use(result_id ResultID)
{
	CResult* Result;

	Result = InstanceMap.at(ResultID);
	if (!Result || Result->ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::InvalidResultID); return nullptr; }
	return Result;
}

void CResult::Drop(result_id ResultID)
{
	CResult* Result;

	Result = InstanceMap.at(ResultID);
	if (!Result || Result->ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::InvalidResultID); return; }
	InstanceMap.erase(ResultID);
	delete Result;
}

FMicron* CResult::Micron(micron_id MicronID, FCursor* CursorPointer)
{
	FCursor Cursor;
	FMicron* Micron;

	if (ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::NoneResult); return nullptr; }
	if (MicronID >= Raw->Size) { MicronML_Throw_Error(EExceptionCode::InvalidMicronID); return nullptr; }

	Cursor.Micron = { ID, MicronID };
	Micron = &Raw->List[MicronID];
	OnMicronEvent->Signal(Micron, Cursor);
	if (CursorPointer) { *CursorPointer = Cursor; }
	return Micron;
}
