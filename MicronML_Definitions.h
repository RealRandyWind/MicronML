#pragma once

namespace MicronML
{
	enum class ECursor : enum_t
	{
		Unknown = MicronML_Unknown,
		Data,
		Result,
		Procedure,
		Sample,
		Micron,
		Compound,
		_EnumSize
	};

	enum class EContact : enum_t
	{
		Unknown = MicronML_Unknown,
		Micron,
		Compound,
		_EnumSize
	};

	enum class EDomain : enum_t
	{
		Unknown = MicronML_Unknown,
		Sample,
		Micron,
		Compound,
		Index,
		_EnumSize
	};

	enum class EShape : enum_t
	{
		Unknown = MicronML_Unknown,
		Micron,
		Compound,
		_EnumSize
	};

	typedef struct FPerformance
	{
		real_t Consistency;
		real_t TypeErrorRatio;
		real_t Error;
		real_t Time;
		size_t SimpleOperations;
		size_t ComplexOperations;
		size_t FunctionCalls;
		size_t Threads;
		size_t N;
	} FPerformance;

	typedef struct FDataPoint
	{
		union
		{
			raw_t Raw[MicronML_RawSize];
			block_t Block;
		};
	} FDataPoint;

	typedef struct FSample
	{
		/* FPoint Min, Max, Mean, SD, Norm; */
		real_t Time, Scale;
		struct { real_t X, Y, Z; } Origin;
		struct { size_t Width, Height, Depth; } Dimensions;
		size_t Size, Channels;
		size_t* ChannelMap;
		union
		{
			FDataPoint* Points;
			raw_t* Pointer;
		};
	} FSample;

	typedef struct FCursor
	{
		ECursor Type;
		union
		{
			struct { result_id ResultID; micron_id ID; } Micron;
			struct { result_id ResultID; compound_id ID; } Compound;
			struct { data_id DataID; sample_id ID; } Sample;
			data_id DataID;
			result_id ResultID;
			procedure_id ProcedureID;
		};
	} FCursor;

	typedef struct FData
	{
		size_t Size;
		FSample* Samples;
	} FData;

	typedef struct FFeature
	{
		real_t Min, Max, Mean, SD, Norm;
		size_t Size;
		real_t* Sequence;
	} FFeature;

	typedef struct FDomain
	{
		EDomain Type;
		size_t Size;
		union
		{
			sample_id* SampleIDs;
			micron_id* MicronIDs;
			compound_id* CompoundIDs;
			size_t* Indices;
		};
	} FDomain;

	typedef struct FSelection
	{
		size_t Size;
		FCursor* Cursors;
	} FSelection;

	typedef struct FPoint
	{
		real_t X, Y, Z, Weight;
	} FPoint;

	typedef struct FShape
	{
		EShape Type;
		struct { FPoint Right, Up, Forward, Origin; } Model;
		FCursor Cursor;
		size_t Size;
		FPoint* Sequence;
	} FShape;

	typedef struct FClass
	{
		class_id ID;
		real_t Score;
	} FClass;

	typedef struct FProfile
	{
		size_t Size;
		FClass* List;
	} FProfile;

	typedef struct FTrace
	{
		size_t Size;
		FShape* Sequence;
	} FTrace;

	typedef struct FContact
	{
		EContact Type;
		contact_id ID;
		union
		{
			micron_id MicronID;
			compound_id CompoundID;
		};
		real_t Point, Weight;
	} FContact;

	typedef struct FFamily
	{
		size_t Size;
		FContact* List;
	} FFamily;

	typedef struct FMicron
	{
		micron_id ID;
		FProfile Profile;
		FTrace Trace;
		FFamily Family;
	} FMicron;

	typedef struct FCompound
	{
		compound_id ID;
		FProfile Profile;
		FTrace Trace;
		FFamily Family;
	} FCompound;

	typedef struct FResult
	{
		struct { size_t Size; FMicron* List; } Microns;
		struct { size_t Size; FCompound* List; } Compounds;
		/* TODO Fix problem of use of multiple procedures */
		FPerformance Performance;
	} FResult;
}

