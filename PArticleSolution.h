#pragma once
#include "Procedure.h"
namespace MicronML
{
	class PArticleSolution :
		public CProcedure
	{
	public:
		PArticleSolution(FProcedureParameters Parameters);
		~PArticleSolution();

		virtual void ExtractMicrons(FExtractMicronParameters Parameters, result_id* ResultIDPointer) override;
		virtual void ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer) override;
		virtual void TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer) override;
		virtual void Train(FTrainParameters Parameters, const FSelection Samples) override;
		virtual void Validate(FValidateParameters Parameters, const FSelection Samples, FPerformance* PerformancePointer) override;
		virtual void Optimize(FOptimizeParameters Parameters) override;
	};
}