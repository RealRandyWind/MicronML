#include "stdafx.h"
#include "Result.h"
#include "Data.h"
#include "PTensorFlow.h"

using namespace MicronML;

PTensorFlow::PTensorFlow(FProcedureParameters Parameters)
	: CProcedure(Parameters)
{
}

PTensorFlow::~PTensorFlow()
{
}

void PTensorFlow::ExtractMicrons(FExtractMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void PTensorFlow::ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void PTensorFlow::TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void PTensorFlow::Train(FTrainParameters Parameters, const FSelection Samples)
{
	CResult* Result;
	CData* Data;
	FFeature Label;
	sample_id SampleID;
	if (!Samples.Size) { return; }
	Active();
	/* TODO train network */
	for (SampleID = MicronML_First; SampleID < Samples.Size; SampleID++)
	{
		/* TODO get data and results, transform results into feature label */
		/* TODO Update(Label, RawData); */
	}
}

void PTensorFlow::Validate(FValidateParameters Parameters, const FSelection Samples, FPerformance* Performance)
{
	CResult* Result;
	CData* Data;
	FFeature Label;
	sample_id SampleID;
	if (!Performance || !Samples.Size) { return; }
	Active();
	/* TODO validate network */
	for (SampleID = MicronML_First; SampleID < Samples.Size; SampleID++)
	{
		/* TODO get data and results, transform results into feature label */
		/* TODO Measure(Label, RawData, Performance); */
	}
}

void PTensorFlow::Optimize(FOptimizeParameters Parameters)
{
	Active();
	/* TODO optimize network */
}