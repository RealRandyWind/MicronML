#include "stdafx.h"
#include "Procedure.h"
#include "Result.h"

#include "PSimpleConvolution.h"
#include "PDeepNeuralNetwork.h"
#include "PEdgeProfile.h"
#include "PHistogramOrientedGradient.h"
#include "PTensorFlow.h"
#include "PArticleSolution.h"
#include "PCurrentFix.h"
#include "PRecurrentNeuralNetwork.h"

using namespace MicronML;

CManagerInitializer* CProcedure::Initializer = new CManagerInitializer(nullptr, Initialize, Terminate);
procedure_id CProcedure::ActiveInstanceID = MicronML_None;
CProcedure::FProcedureMap CProcedure::InstanceMap = { nullptr };

CProcedure::CProcedure(FProcedureParameters Parameters)
{
}

bool_t CProcedure::Initialize()
{
	InstanceMap.fill(nullptr);
	return true;
}

bool_t CProcedure::Terminate()
{
	return true;
}

CProcedure * CProcedure::Built(FProcedureParameters Parameters, EProcedureType Type)
{
	switch (Type)
	{
		case EProcedureType::SimpleConvolution:
			return new CPSimpleConvolution(Parameters);
		case EProcedureType::DeepNeuralNetwork :
			return new PDeepNeuralNetwork(Parameters);
		case EProcedureType::EdgeProfile:
			return new PEdgeProfile(Parameters);
		case EProcedureType::HistogramOrientedGradient:
			return new PHistogramOrientedGradient(Parameters);
		case EProcedureType::TensorFlow:
			return new PTensorFlow(Parameters);
		case EProcedureType::ArticleSolution:
			return new PArticleSolution(Parameters);
		case EProcedureType::CurrentFix:
			return new PCurrentFix(Parameters);
		case EProcedureType::RecurrentNeuralNetwork:
			return new PRecurrentNeuralNetwork(Parameters);
		default:
			return nullptr;
	}
}

CProcedure::~CProcedure()
{
}

CProcedure* CProcedure::Make(FProcedureParameters Parameters)
{
	CProcedure* Procedure;

	Procedure = Built(Parameters, Parameters.Type);
	if (!Procedure || !Procedure->ID) { return nullptr; }
	Procedure->Active();
	return Procedure;
}

CProcedure* CProcedure::Use(procedure_id ProcedureID)
{
	CProcedure* Procedure;

	if (!ProcedureID || ProcedureID <= InstanceMap.size()) { return nullptr; }
	Procedure = InstanceMap[ProcedureID];
	if (!Procedure || !Procedure->ID) { return nullptr; }
	Procedure->Active();
	return Procedure;
}

void CProcedure::Drop(procedure_id ProcedureID)
{
	CProcedure* Procedure;
	if (!ProcedureID || ProcedureID <= InstanceMap.size()) { return; }
	Procedure = InstanceMap.at(ProcedureID);
	if (!Procedure) { return; }
	InstanceMap[ProcedureID] = nullptr;
	delete Procedure;
}

void CProcedure::Active()
{
	if (ActiveInstanceID == ID) { return; }
	ActiveInstanceID = ID;
}

procedure_id CProcedure::GetID()
{
	return ID;
}

