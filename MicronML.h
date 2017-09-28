#pragma once

#ifdef MICRONML_EXPORTS
#define MICRONML_API __declspec(dllexport)
#else
#define MICRONML_API __declspec(dllimport)
#endif

#include "MicronML_Exceptions.h"
#include "MicronML_Parameters.h"
#include "MicronML_Definitions.h"
#include "MicronML_Events.h"
#include "ExceptionManager.h"

namespace MicronML
{
	class MICRONML_API CMicronML final
	{
	public:
		~CMicronML();
		static CMicronML* GetInstance();

		void ImportData(const FDataParameters Parameters, data_id* DataIDPointer);
		void ImportProcedure(const FProcedureParameters Parameters, procedure_id* ProcedureIDPointer);
		void ImportResult(const FResultParameters Parameters, result_id *ResultIDPointer);

		void ExtractMicrons(const FExtractMicronParameters Parameters, result_id* ResultsIDPointer);
		void ClassifyMicrons(const FClassifyMicronParameters Parameters, result_id* ResultsIDPointer);
		void TraceMicrons(const FTraceMicronParameters Parameters, result_id* ResultsIDPointer);
		
		/*
		void ExtractCompounds(const FExtractCompoundParameters Parameters, result_id* ResultsIDPointer);
		void ClassifyCompounds(const FClassifyCompoundParameters, Parameters, result_id* ResultsIDPointer);
		void TraceCompounds(const FTraceCompoundParameters, Parameters, result_id* ResultsIDPointer);
		*/

		void TrainProcedure(const FTrainParameters Parameters, const FSelection Samples);
		void ValidateProcedure(const FValidateParameters Parameters, const FSelection Samples, FPerformance* PerformancePointer);
		void OptimizeProcedure(const FOptimizeParameters Parameters);

		void Sample(const FCursor Cursor);
		void Micron(const FCursor Cursor);
		void Compound(const FCursor Cursor);

		void AddDelegate(FOnSampleEvent::FDelegate Delegate, data_id DataID);
		void AddDelegate(FOnMicronEvent::FDelegate Delegate, result_id ResultID);
		void AddDelegate(FOnDataImportEvent::FDelegate Delegate);
		void AddDelegate(FOnDataImportDoneEvent::FDelegate Delegate);

		void AddDelegate(FOnExceptionEvent::FDelegate Delegate);
		void RemoveDelegate(FOnExceptionEvent::FDelegate Delegate);
		void UseDefaultExceptionListener();
	
	private:
		CMicronML();
		static CMicronML* Instance;

	private:
		FOnDataImportEvent* OnDataImportEvent;
		FOnDataImportDoneEvent* OnDataImportDoneEvent;
	};
}
