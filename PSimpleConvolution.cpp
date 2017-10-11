#include "stdafx.h"
#include <math.h>
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

	/* Exceptions Preconditional */
	if (!ResultIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullResultIDPointer); return; }
	
	Active();
	Data = CData::Use(Parameters.DataID);
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void CPSimpleConvolution::ClassifyMicrons(FClassifyMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;

	/* Exceptions Preconditional */
	if (!ResultIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullResultIDPointer); return; }
	
	Active();
	Data = CData::Use(Parameters.DataID);
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void CPSimpleConvolution::TraceMicrons(FTraceMicronParameters Parameters, result_id* ResultIDPointer)
{
	CResult* Result;
	CData* Data;

	/* Exceptions Preconditional */
	if (!ResultIDPointer) { MicronML_Throw_Warning(EExceptionCode::NullResultIDPointer); return; }
	
	Active();
	Data = CData::Use(Parameters.DataID);
	/* TODO prepair result data, and data then run it */
	*ResultIDPointer = Result->GetID();
}

void CPSimpleConvolution::Train(FTrainParameters Parameters, const FSelection Selection)
{
	CResult* Result;
	CData* Data;
	FFeature Label;
	sample_id SampleID;

	/* Exceptions Preconditional */
	if (!Selection.Size) { MicronML_Throw_Warning(EExceptionCode::EmptySelection); return; }
	
	Active();
	/* TODO train network */
	for (SampleID = MicronML_First; SampleID < Selection.Size; SampleID++)
	{
		/* TODO get data and results, transform results into feature label */
		/* TODO Update(Label, RawData); */
	}
}

void CPSimpleConvolution::Validate(FValidateParameters Parameters, const FSelection Selection, FPerformance* Performance)
{
	CResult* Result;
	CData* Data;
	FResult* Raw;
	FSample* Sample;
	FCursor Cursor, SampleCursor;
	FMicron Micron;
	FShape Shape;
	FLabel Label;
	sample_id SampleID;
	micron_id MicronID;
	shape_id ShapeID;
	size_t CursorID;

	MicronML_Throw_Ignorant();

	/* Exceptions Preconditional */
	if (!Performance) { MicronML_Throw_Warning(EExceptionCode::NullPerformance); return; }
	if (!Selection.Size) { MicronML_Throw_Warning(EExceptionCode::EmptySelection); return; }

	Active();
	/* TODO validate network */
	for (CursorID = MicronML_First; CursorID < Selection.Size; CursorID++)
	{
		Cursor = Selection.Cursors[CursorID];
		if (Cursor.Type != ECursor::Result) { MicronML_Throw_Warning(EExceptionCode::InvalidCursorType); continue; }
		Result = CResult::Use(Cursor.ResultID);
		if (!Result) { MicronML_Throw_Warning(EExceptionCode::NullResult); return; }
		Raw = Result->GetRaw();
		for (MicronID = MicronML_First; MicronID < Raw->Microns.Size; ++MicronID)
		{
			Micron = Raw->Microns.List[MicronID];
			for (ShapeID = MicronML_First; ShapeID < Micron.Trace.Size; ++ShapeID)
			{
				Shape = Micron.Trace.List[ShapeID];
				Data = CData::Use(Shape.Cursor.Sample.DataID);
				if (!Data) { MicronML_Throw_Warning(EExceptionCode::NullData); return; }
				Sample = Data->GetSample(SampleCursor.Sample.ID, nullptr);

				Measure(Label, *Sample, Performance, ExtractNetworkPointer);
			}
		}
	}
}

void CPSimpleConvolution::Optimize(FOptimizeParameters Parameters)
{
	MicronML_Throw_NotSupported();

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
	real_t Charge;

	/* Exceptions Preconditional */
	if (!NetworkPointer) { MicronML_Throw_Warning(EExceptionCode::NullNetwork); return; }
	if (!Feature) { MicronML_Throw_Warning(EExceptionCode::NullFeature);  return; }

	/* Initialization */
	Network = (FNetwork*) NetworkPointer;
	bActive = true;
	Output = Buffer[bActive];
	Input = Buffer[!bActive];
	Output.Values = new real_t[Network->MaximumLayerSize];
	Input.Values = new real_t[Network->MaximumLayerSize];
	Output.Size = Domain.Size;

	/* Convert data domain as output charge of input layer */
	for (ValueID = MicronML_First; ValueID < Domain.Size; ValueID++)
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
			/* Compute activation given previous layer activations */
			Neuron = Layer.Neurons[NeuronID];
			Charge = -Layer.Bias;
			for (ChargeID = MicronML_First; ChargeID < Input.Size; ChargeID++)
			{
				Charge += Input.Values[ChargeID] * Neuron.Weights[ChargeID];
			}
			Output.Values[NeuronID] = Activation(Charge);
		}
	}

	/* Convert output of network to feature */
	for (ValueID = MicronML_First; ValueID < Feature->Size; ValueID++)
	{
		Feature->Sequence[ValueID] = Output.Values[ValueID];
	}

	/* Deinitialization */
	delete[] Input.Values;
	delete[] Output.Values;
}

void CPSimpleConvolution::Update(const FLabel Label, const FSample Sample, pointer_t NetworkPointer)
{
	FNetwork* Network;
	FFeature Feature, Target;
	real_t Delta, Error, Difference, Dominator;
	size_t PointId, ValueID;

	/* Exceptions Preconditional */
	if (!NetworkPointer) { MicronML_Throw_Warning(EExceptionCode::NullNetwork); return; }

	

	/* Initialization */
	Network = (FNetwork*) NetworkPointer;

}

void CPSimpleConvolution::Measure(const FLabel Label, const FSample Sample, FPerformance* Performance, pointer_t NetworkPointer)
{
	FNetwork* Network;
	FFeature Feature, Target;
	real_t Error, Difference, Dominator;
	size_t PointID, ValueID;

	/* Exceptions Preconditional */
	if (!NetworkPointer) { MicronML_Throw_Warning(EExceptionCode::NullNetwork); return; }
	if (!Sample.Size) { MicronML_Throw_Warning(EExceptionCode::EmptySample); return; }

	/* Initialization */
	Network = (FNetwork*) NetworkPointer;
	Error = MicronML_ZeroF;
	Dominator = MicronML_OneF / Sample.Size;

	/* Compute error contribution of current sample */
	for (PointID = MicronML_First; PointID < Sample.Size; ++PointID)
	{
		/* Forward propagation of the sample */
		Apply(Neighbourhoud(PointID), Sample, &Feature, NetworkPointer);

		/* compute feature error compared to target feature */
		Target = Label.Targets[PointID];
		for (ValueID = MicronML_First; ValueID < Feature.Size; ++ValueID)
		{
			Difference = Target.Sequence[ValueID] - Feature.Sequence[ValueID];
			Error += Difference * Difference;
		}
	}
	Error *= Dominator;

	/* Update error as moving avrage, assuming N is incremented */
	Performance->Error += (Error - Performance->Error) / Performance->N;
}

inline real_t CPSimpleConvolution::Activation(real_t Charge)
{
	/*
	return (Charge < MicronML_ZeroF ? MicronML_ZeroF : (Charge > MicronML_OneF ? MicronML_OneF : Charge));
	*/
	return MicronML_OneF / (MicronML_OneF + exp(Charge));
}

inline real_t CPSimpleConvolution::DeltaActivation(real_t Charge)
{
	real_t ExpCharge, Dominator;

	ExpCharge = exp(Charge);
	Dominator = (ExpCharge + MicronML_OneF) * (ExpCharge + MicronML_OneF);
	return ExpCharge * (MicronML_OneF / Dominator);
}

inline FDomain CPSimpleConvolution::Neighbourhoud(size_t PointID)
{
	FDomain Domain;
	
	Domain = { MicronML_Zero, nullptr };
	return Domain;
}