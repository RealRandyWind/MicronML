#pragma once

#include <array>
#include "ManagerInitializer.h"

namespace MicronML
{
	class CProcedure
	{
		typedef std::array<CProcedure*, (size_t)EProcedureType::_EnumSize> FProcedureMap;
	public:
		CProcedure(FProcedureParameters Parameters);
		virtual ~CProcedure();
		static CProcedure* Make(FProcedureParameters Parameters);
		static CProcedure* Use(procedure_id ProcedureID);
		static void Drop(procedure_id ProcedureID);

		virtual void Active();
		/*
		virtual void ExtractCompounds(FExtractCompoundParameters Parameters, result_id* ResultIDPointer) = 0;
		virtual void ClassifyCompounds(FClassifyCompoundParameters Parameters, result_id* ResultIDPointer) = 0;
		virtual void TraceCompounds(FTraceCompoundParameters Parameters, result_id* ResultIDPointer) = 0;
		*/
		virtual void ExtractMicrons(FExtractMicronParameters Parameters, result_id* ResultIDPointer) = 0;
		virtual void ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer) = 0;
		virtual void TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer) = 0;
		virtual void Train(FTrainParameters Parameters, const FSelection Samples) = 0;
		virtual void Validate(FValidateParameters Parameters, const FSelection Samples, FPerformance* PerformancePointer) = 0;
		virtual void Optimize(FOptimizeParameters Parameters) = 0;
		virtual procedure_id GetID() final;
	private:	
		static FProcedureMap InstanceMap;
		static procedure_id ActiveInstanceID;
		static CManagerInitializer* Initializer;
		static bool_t Initialize();
		static bool_t Terminate();
		static CProcedure* Built(FProcedureParameters Parameters, EProcedureType Type);

		procedure_id ID;
	};
}
