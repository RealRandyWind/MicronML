#include "stdafx.h"
#include "Result.h"
#include "Data.h"
#include "PSimpleConvolution.h"
#include "PSimpleConvolution_Definitions_Private.h"

using namespace MicronML;
using namespace PSimpleConvolution;

CPSimpleConvolution::CPSimpleConvolution(FProcedureParameters Parameters)
	: CProcedure(Parameters)
{
}

CPSimpleConvolution::~CPSimpleConvolution()
{
}

void CPSimpleConvolution::ExtractMicrons(FExtractMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	Data = CData::Use(Parameters.DataID);
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void CPSimpleConvolution::ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	Data = CData::Use(Parameters.DataID);
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void CPSimpleConvolution::TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;
	if (!ResultIDPointer) { return; }
	Active();
	Data = CData::Use(Parameters.DataID);
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void CPSimpleConvolution::Train(FTrainParameters Parameters, const FSelection Samples)
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

void CPSimpleConvolution::Validate(FValidateParameters Parameters, const FSelection Samples, FPerformance* Performance)
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
		/* TODO Measure(Label, RawData, Performance, ); */
	}
}

void CPSimpleConvolution::Optimize(FOptimizeParameters Parameters)
{
	Active();
	/* TODO optimize network(s) */
}

void CPSimpleConvolution::Apply(FDomain Domain, const FSample Sample, FFeature* Feature, pointer_t NetworkPointer)
{
	FNetwork* Network;

	FLayer Layer;
	FCharge Buffer[2], Output, Input;
	FNeuron Neuron;
	FDataPoint Point;
	size_t LayerID, NeuronID, ChargeID, ValueID;
	bool_t bActive;

	if (!Feature || !NetworkPointer) { return;  }

	/* Initialization */
	Network = (FNetwork*) NetworkPointer;
	bActive = true;
	Output = Buffer[bActive];
	Input = Buffer[!bActive];
	Output.Values = new real_t[Network->MaximumLayerSize];
	Input.Values = new real_t[Network->MaximumLayerSize];
	Output.Size = Domain.Size;

	/* Convert data domain as output charge of input layer */
	for (ValueID = MicronML_First; ValueID < Domain.Size; ValueID += 2)
	{
		Point = Sample.Points[Domain.Indices[ValueID]];
		Output.Values[ValueID] = Point.Block;
		/* TODO handle more channels */
	}

	/* Propagate charge trough the network */
	for (LayerID = MicronML_First; LayerID < Network->Size; LayerID++)
	{
		/* Swap buffer, make output the input */
		bActive = !bActive;
		Output = Buffer[bActive];
		Input = Buffer[!bActive];

		/* Compute output of layer using input */
		Layer = Network->Layers[LayerID];
		Output.Size = Layer.Size;
		for (NeuronID = MicronML_First; NeuronID < Layer.Size; NeuronID++)
		{
			Neuron = Layer.Neurons[NeuronID];
			Output.Values[NeuronID] = Layer.Bias;
			for (ChargeID = MicronML_First; ChargeID < Input.Size; ChargeID++)
			{
				Output.Values[NeuronID] += Input.Values[ChargeID] * Neuron.Weights[ChargeID];
			}
		}
	}

	/* Convert output of network to results */
	for (ValueID = MicronML_First; ValueID < Feature->Size; ValueID++)
	{
		Feature->Sequence[ValueID] = Output.Values[ValueID];
	}

	/* Deinitialization */
	delete[] Input.Values;
	delete[] Output.Values;
}

void CPSimpleConvolution::Update(const FFeature Label, const FSample Sample, pointer_t NetworkPointer)
{
	FNetwork* Network;
	FFeature Feature;
	if (!NetworkPointer) { return; }

	/* Initialization */
	Network = (FNetwork*)NetworkPointer;
}

void CPSimpleConvolution::Measure(const FFeature Label, const FSample Sample, FPerformance* Performance, pointer_t NetworkPointer)
{
	FNetwork* Network;
	FFeature Feature;
	if (!Performance || !NetworkPointer) { return; }

	/* Initialization */
	Network = (FNetwork*)NetworkPointer;
}
