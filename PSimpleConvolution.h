#pragma once
#include "Procedure.h"

namespace MicronML
{
	class CPSimpleConvolution :
		public CProcedure
	{
	public:
		CPSimpleConvolution(FProcedureParameters Parameters);
		~CPSimpleConvolution();

		virtual void ExtractMicrons(FExtractMicronParameters Parameters, result_id* ResultIDPointer) override;
		virtual void ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer) override;
		virtual void TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer) override;
		virtual void Train(FTrainParameters Parameters, const FSelection Samples) override;
		virtual void Validate(FValidateParameters Parameters, const FSelection Samples, FPerformance* PerformancePointer) override;
		virtual void Optimize(FOptimizeParameters Parameters) override;
	private:
		pointer_t ExtractNetworkPointer;
		pointer_t ClassifyNetworkPointer;
		pointer_t TraceNetworkPointer;

		void Apply(FDomain Domain, const FSample Sample, FFeature* Feature, pointer_t NetworkPointer);
		void Update(const FFeature Label, const FSample Sample, pointer_t NetworkPointer);
		void Measure(const FFeature Label, const FSample Sample, FPerformance* Performance, pointer_t NetworkPointer);
	};
}