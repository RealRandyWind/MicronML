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
	OnCompoundEvent = new FOnCompoundEvent();
}

CResult::~CResult()
{
	if (Raw->Microns.List)
	{
		for (micron_id MicronID = MicronML_First; MicronID < Raw->Microns.Size; ++MicronID)
		{
			FMicron& Micron = Raw->Microns.List[MicronID];
			if (Micron.Profile.List) { delete[] Micron.Profile.List; }
			if (Micron.Family.List) { delete[] Micron.Family.List; }
			if (Micron.Trace.List)
			{
				for (shape_id ShapeID = MicronML_First; ShapeID < Micron.Trace.Size; ++ShapeID)
				{
					FShape& Shape = Micron.Trace.List[ShapeID];
					if (Shape.Sequence) { delete[] Shape.Sequence; }
				}
				delete[] Micron.Trace.List;
			}
		}
		delete[] Raw->Microns.List;
	}

	if (Raw->Compounds.List)
	{
		for (compound_id CompoundID = MicronML_First; CompoundID < Raw->Compounds.Size; ++CompoundID)
		{
			FCompound& Compound = Raw->Compounds.List[CompoundID];
			if (Compound.Profile.List) { delete[] Compound.Profile.List; }
			if (Compound.Family.List) { delete[] Compound.Family.List; }
			if (Compound.Trace.List)
			{
				for (shape_id ShapeID = MicronML_First; ShapeID < Compound.Trace.Size; ++ShapeID)
				{
					FShape& Shape = Compound.Trace.List[ShapeID];
					if (Shape.Sequence) { delete[] Shape.Sequence; }
				}
				delete[] Compound.Trace.List;
			}
		}
		delete[] Raw->Compounds.List;
	}

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

FMicron* CResult::GetMicron(micron_id MicronID, FCursor* CursorPointer)
{
	FCursor Cursor;
	FMicron* Micron;

	if (ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::NoneResult); return nullptr; }
	if (MicronID >= Raw->Microns.Size) { MicronML_Throw_Error(EExceptionCode::InvalidMicronID); return nullptr; }

	Cursor.Type = ECursor::Micron;
	Cursor.Micron = { ID, MicronID };
	Micron = &Raw->Microns.List[MicronID];
	OnMicronEvent->Signal(Micron, Cursor);
	if (CursorPointer) { *CursorPointer = Cursor; }
	return Micron;
}

FCompound* CResult::GetCompound(compound_id CompoundID, FCursor* CursorPointer)
{
	FCursor Cursor;
	FCompound* Compound;

	if (ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::NoneResult); return nullptr; }
	if (CompoundID >= Raw->Compounds.Size) { MicronML_Throw_Error(EExceptionCode::InvalidCompoundID); return nullptr; }

	Cursor.Type = ECursor::Compound;
	Cursor.Compound = { ID, CompoundID };
	Compound = &Raw->Compounds.List[CompoundID];
	OnCompoundEvent->Signal(Compound, Cursor);
	if (CursorPointer) { *CursorPointer = Cursor; }
	return Compound;
}

