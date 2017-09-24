#pragma once

#ifdef MICRONML_EXPORTS
#define MICRONML_API __declspec(dllexport)
#else
#define MICRONML_API __declspec(dllimport)
#endif

#include "MicronML_Types.h"

namespace MicronML
{
	enum class EExceptionType : enum_t
	{
		Unknown,
		Warning,
		Error,
		Success,
		Info,
		Log,
		Debug,
		_EnumSize
	};

	enum class EExceptionCode : enum_t
	{
		Unknown,
		NullSingeltonInstance,
		NullDataRaw,
		NullResultRaw,
		NullExceptionListener,
		NullData,
		NullProcedure,
		NullResult,
		NullReturn,
		NullFile,
		NoneData,
		NoneResult,
		NoneProcedure,
		NullIDPointer,
		NullDataIDPointer,
		NullProcedureIDPointer,
		NullResultIDPointer,
		NullPointer,
		FaildOpenFile,
		FaildToImportFile,
		FaildToExportFile,
		FaildToAllocateSamples,
		FaildToAllocateMicrons,
		FaildToAllocateShapes,
		FaildToAllocateClasses,
		FaildToAllocateMicronPoints,
		FaildToAllocateDataPoints,
		FaildToAllocateContacts,
		FaildToAllocateCursors,
		FaildToAllocateFeatures,
		FaildTermination,
		FaildInitialization,
		FunctionNotSuppored,
		FunctionDeprecated,
		InvalidSampleID,
		InvalidMicronID,
		InvalidDataID,
		InvalidResultID,
		InvalidProcedureID,
		DataImport,
		ResultImport,
		ProcedureImport,
		_EnumSize
	};

	typedef struct FException
	{
		EExceptionType Type;
		EExceptionCode Code;
		const string_t FunctionSignature;
		const string_t File;
		size_t Line;
		pointer_t OtherPointer;
	} FException;
}

