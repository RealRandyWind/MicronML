#include "stdafx.h"
#include "Data.h"

using namespace MicronML;

CManagerInitializer* CData::Initializer = new CManagerInitializer(nullptr, Initialize, Terminate);
data_id CData::InstanceIDCounter = MicronML_One;
CData::FInstanceMap CData::InstanceMap = { { MicronML_None, nullptr } };

CData::CData(FDataParameters Parameters)
{
	ID = MicronML_None;
	Raw = new FData();
	Raw->Samples = nullptr;
	Raw->Size = MicronML_Zero;
	OnSampleEvent = new FOnSampleEvent();
}

CData::~CData()
{
	if (Raw->Samples)
	{
		for (size_t PointID = MicronML_First; PointID < Raw->Size; ++PointID)
		{
			FSample& Sample = Raw->Samples[PointID];
			if (Sample.Pointer) { delete[] Sample.Pointer; }
			if (Sample.Channels.Bits) { delete[] Sample.Channels.Bits; }
		}
		delete[] Raw->Samples;
	}
	delete Raw;
	delete OnSampleEvent;
}

data_id CData::GetID()
{
	return ID;
}

FData* CData::GetRaw()
{
	if (ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::NoneData); return nullptr; }
	return Raw;
}

bool_t CData::Initialize()
{
	return true;
}

bool_t CData::Terminate()
{
	return true;
}

CData* CData::Make(FDataParameters Parameters)
{
	CData* Data;

	Data = new CData(Parameters);
	Data->ID = InstanceIDCounter++;
	InstanceMap[Data->ID] = Data;
	return Data;
}

CData* CData::Use(data_id DataID)
{
	CData* Data;

	Data = InstanceMap.at(DataID);
	if (!Data || Data->ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::InvalidDataID); return nullptr; }
	return Data;
}

void CData::Drop(data_id DataID)
{
	CData* Data;

	if (!DataID) { return; }
	Data = InstanceMap.at(DataID);
	if (!Data || Data->ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::InvalidDataID); return; }
	InstanceMap.erase(DataID);
	delete Data;
}

FSample* CData::GetSample(sample_id SampleID, FCursor* CursorPointer)
{
	FCursor Cursor;
	FSample* Sample;

	if (ID == MicronML_None) { MicronML_Throw_Warning(EExceptionCode::NoneData); return nullptr; }
	if (SampleID >= Raw->Size) { MicronML_Throw_Error(EExceptionCode::InvalidSampleID); return nullptr; }

	Cursor.Type = ECursor::Sample;
	Cursor.Sample = { ID, SampleID };
	Sample = &Raw->Samples[SampleID];
	OnSampleEvent->Signal(Sample, Cursor);
	if (CursorPointer) { *CursorPointer = Cursor; }
	return Sample;
}
