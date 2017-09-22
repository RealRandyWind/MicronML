#include "stdafx.h"
#include "MicronML.h"
#include "Data.h"
#include "Result.h"
#include "Procedure.h"

using namespace MicronML;

CMicronML* CMicronML::Instance = nullptr;

CMicronML::CMicronML()
{
	OnDataImportEvent = new FOnDataImportEvent;
	OnDataImportDoneEvent = new FOnDataImportDoneEvent;
}

CMicronML::~CMicronML()
{
	delete OnDataImportEvent;
	delete OnDataImportDoneEvent;
}

CMicronML* CMicronML::GetInstance()
{
	if (!Instance) { Instance = new CMicronML();  }
	return Instance;
}

void CMicronML::ImportData(const FDataParameters Parameters, data_id* DataIDPointer)
{
	CData* Data;
	FData* Raw;
	data_id DataID;

	if (!DataIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullDataIDPointer); return;  }
	Data = CData::Make(Parameters);
	if (!Data) { MicronML_Throw_Warning(EExceptionCode::NullData); return; }
	DataID = Data->GetID();
	Raw = Data->GetRaw();
	*DataIDPointer = DataID;
	OnDataImportEvent->Signal(Parameters, Raw, DataID);
	OnDataImportDoneEvent->Signal(Parameters, *Raw, DataID);
}

void CMicronML::ImportResult(const FResultParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	FResult* Raw;
	result_id ResultID;

	if (!ResultIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullResultIDPointer); return; }
	Result = CResult::Make(Parameters);
	if (!Result) { MicronML_Throw_Warning(EExceptionCode::NullResult); return; }
	ResultID = Result->GetID();
	Raw = Result->GetRaw();
	*ResultIDPointer = ResultID;
}

void CMicronML::ImportProcedure(const FProcedureParameters Parameters, procedure_id* ProcedureIDPointer)
{
	CProcedure* Procedure;

	if (!ProcedureIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullProcedureIDPointer);  return; }
	Procedure = CProcedure::Make(Parameters);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	*ProcedureIDPointer = Procedure->GetID();
}

void CMicronML::ExtractMicrons(const FExtractMicronParameters Parameters, result_id* ResultsIDPointer)
{
	CProcedure* Procedure;

	if (!ResultsIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullProcedureIDPointer); return; }
	Procedure = CProcedure::Use(Parameters.ProcedureID);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	Procedure->ExtractMicrons(Parameters, ResultsIDPointer);
}

void CMicronML::ClassifyMicrons(const FClassifyMicronParameters Parameters, result_id* ResultsIDPointer)
{
	CProcedure* Procedure;

	if (!ResultsIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullResultIDPointer); return; }
	Procedure = CProcedure::Use(Parameters.ProcedureID);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	Procedure->ClassifyMicrons(Parameters, ResultsIDPointer);
}

void CMicronML::TraceMicrons(const FTraceMicronParameters Parameters, result_id* ResultsIDPointer)
{
	CProcedure* Procedure;

	if (!ResultsIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullProcedureIDPointer); return; }
	Procedure = CProcedure::Use(Parameters.ProcedureID);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	Procedure->TraceMicrons(Parameters, ResultsIDPointer);
}

void CMicronML::TrainProcedure(const FTrainParameters Parameters, const FSelection Samples)
{
	CProcedure* Procedure;

	Procedure = CProcedure::Use(Parameters.ProcedureID);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	Procedure->Train(Parameters, Samples);
}

void CMicronML::ValidateProcedure(const FValidateParameters Parameters, const FSelection Samples, FPerformance* PerformancePointer)
{
	CProcedure* Procedure;

	Procedure = CProcedure::Use(Parameters.ProcedureID);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	Procedure->Validate(Parameters, Samples, PerformancePointer);
}

void CMicronML::OptimizeProcedure(const FOptimizeParameters Parameters)
{
	CProcedure* Procedure;

	Procedure = CProcedure::Use(Parameters.ProcedureID);
	if (!Procedure) { MicronML_Throw_Warning(EExceptionCode::NullProcedure); return; }
	Procedure->Optimize(Parameters);
}

void CMicronML::Sample(const FCursor Cursor)
{
	CData* Data;
	Data = CData::Use(Cursor.Sample.DataID);
	if (!Data) { MicronML_Throw_Warning(EExceptionCode::NullData); return; }
	Data->Sample(Cursor.Sample.ID, nullptr);
}

void CMicronML::Micron(const FCursor Cursor)
{
	CResult* Result;
	Result = CResult::Use(Cursor.Micron.ResultID);
	if (!Result) { MicronML_Throw_Warning(EExceptionCode::NullResult); return; }
	Result->Micron(Cursor.Micron.ID, nullptr);
}

void CMicronML::AddDelegate(FOnSampleEvent::FDelegate Delegate, data_id DataID)
{
	CData* Data;
	Data = CData::Use(DataID);
	if (!Data) { MicronML_Throw_Warning(EExceptionCode::NullData); return; }
	Data->OnSampleEvent->Add(Delegate);
}

void CMicronML::AddDelegate(FOnMicronEvent::FDelegate Delegate, result_id ResultID)
{
	CResult* Result;
	Result = CResult::Use(ResultID);
	if (!Result) { MicronML_Throw_Warning(EExceptionCode::NullData); return; }
	Result->OnMicronEvent->Add(Delegate);
}

void CMicronML::AddDelegate(FOnDataImportEvent::FDelegate Delegate)
{
	OnDataImportEvent->Add(Delegate);
}

void CMicronML::AddDelegate(FOnDataImportDoneEvent::FDelegate Delegate)
{
	OnDataImportDoneEvent->Add(Delegate);
}

void CMicronML::AddDelegate(FOnExceptionEvent::FDelegate Delegate)
{
	CExceptionManager::GetInstance()->OnExceptionEvent.Add(Delegate);
}

void CMicronML::RemoveDelegate(FOnExceptionEvent::FDelegate Delegate)
{
	CExceptionManager::GetInstance()->OnExceptionEvent.Remove(Delegate);
}

void CMicronML::UseDefaultExceptionListener()
{
	CExceptionManager::UseDefaultCatch();
}