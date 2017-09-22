#include "stdafx.h"
#include "Result.h"
#include "Data.h"
#include "PDeepNeuralNetwork.h"

using namespace MicronML;

PDeepNeuralNetwork::PDeepNeuralNetwork(FProcedureParameters Parameters)
	: CProcedure(Parameters)
{
}

PDeepNeuralNetwork::~PDeepNeuralNetwork()
{
}

void PDeepNeuralNetwork::ExtractMicrons(FExtractMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void PDeepNeuralNetwork::ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void PDeepNeuralNetwork::TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void PDeepNeuralNetwork::Train(FTrainParameters Parameters, const FSelection Samples)
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

void PDeepNeuralNetwork::Validate(FValidateParameters Parameters, const FSelection Samples, FPerformance* Performance)
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

void PDeepNeuralNetwork::Optimize(FOptimizeParameters Parameters)
{
	Active();
	/* TODO optimize network */
}