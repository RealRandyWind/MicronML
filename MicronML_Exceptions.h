#pragma once

#include "MicronML_Types.h"

namespace MicronML
{
	enum class EExceptionType : enum_t
	{
		Unknown = MicronML_Unknown,
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
		Unknown = MicronML_Unknown,

		NullPointer = MicronML_NullCode,
		NullSingeltonInstance,
		NullDataRaw,
		NullResultRaw,
		NullExceptionListener,
		NullData,
		NullProcedure,
		NullResult,
		NullReturn,
		NullFile,
		NullIDPointer,
		NullDataIDPointer,
		NullProcedureIDPointer,
		NullResultIDPointer,
		NullTrace,
		NullNetwork,
		NullFeature,
		NullPerformance,

		NoneData = MicronML_NoneCode,
		NoneResult,
		NoneProcedure,

		FaildOpenFile = MicronML_FaildCode,
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
		FaildToAllocateCompounds,
		FaildTermination,
		FaildInitialization,
		FaildToReadSampleSize,

		InvalidSampleID = MicronML_InvalidCode,
		InvalidMicronID,
		InvalidDataID,
		InvalidResultID,
		InvalidProcedureID,
		InvalidShapeID,
		InvalidContactID,
		InvalidClassID,
		InvalidCompoundID,

		DataImport = MicronML_ActionCode,
		ResultImport,
		ProcedureImport,

		FunctionNotSuppored = MicronML_SpecialCode,
		FunctionDeprecated,
		FunctionBeta,

		EmptySample = MicronML_OtherCode,

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

