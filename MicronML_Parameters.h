#pragma once

#include "MicronML_Types.h"

namespace MicronML
{
	typedef struct FProcedureParameters
	{
		EProcedureType Type;
		string_t File;
		real_t Precision;
		real_t Performence;
		real_t Persistance;
	} FProcedureParameters;

	typedef struct FDataParameters
	{
		string_t File;
	} FDataParameters;

	typedef struct FResultParameters
	{
		string_t File;
	} FResultParameters;

	typedef struct FExtractMicronParameters
	{
		/* TODO define attributes */
		procedure_id ProcedureID;
		data_id DataID;
	} FExtractMicronParameters;

	typedef struct FClassifyMicronParameters
	{
		/* TODO define attributes */
		procedure_id ProcedureID;
		data_id DataID;
	} FClassifyMicronParameters;

	typedef struct FTraceMicronParameters
	{
		/* TODO define attributes */
		procedure_id ProcedureID;
		data_id DataID;
	} FTraceMicronParameters;

	typedef struct FTrainParameters
	{
		/* TODO define attributes */
		procedure_id ProcedureID;
	} FTrainParameters;

	typedef struct FValidateParameters
	{
		/* TODO define attributes */
		procedure_id ProcedureID;
	} FValidateParameters;

	typedef struct FOptimizeParameters
	{
		/* TODO define attributes */
		procedure_id ProcedureID;
	} FOptimizeParameters;
}

