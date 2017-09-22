#pragma once

namespace MicronML
{
	typedef struct FPerformance
	{
		real_t Consistency;
		real_t TypeErrorRatio;
		real_t Error;
		real_t Time;
		size_t SimpleOperations;
		size_t ComplexOperations;
		size_t FunctionCalls;
		size_t N;
	} FPerformance;

	typedef struct FDataPoint
	{
		union
		{
			real_t Real[MicronML_RealSize];
			raw_t Raw[MicronML_RawSize];
			block_t Block;
		};
	} FDataPoint;

	typedef struct FSample
	{
		/* FDataPoint Min, Max, Mean, SD, Norm; */
		real_t Time;
		size_t OriginX, OriginY;
		size_t Width, Height, Channels;
		union
		{
			FDataPoint* Points;
			raw_t* Pointer;
		};
	} FSample;

	typedef struct FCursor
	{
		union
		{
			struct { data_id DataID; sample_id ID; } Sample;
			struct { result_id ResultID; micron_id ID; } Micron;
			struct { data_id ID; } Data;
			struct { result_id ID; } Result;
			struct { procedure_id ID; } Procedure;
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
		size_t Size;
		union
		{
			sample_id* SampleIDs;
			micron_id* MicronIDs;
			class_id* ClassIDs;
			shape_id* ShapeIDs;
			size_t* Indices;
		};
	} FDomain;

	typedef struct FSelection
	{
		size_t Size;
		FCursor* Cursors;
	} FSelection;

	typedef struct FMicronPoint
	{
		real_t X, Y, Z, Weight;
	} FMicronPoint;

	typedef struct FMicronShape
	{
		shape_id ID;
		FCursor Cursor;
		size_t Size;
		FMicronPoint* Sequence;
	} FMicronShape;

	typedef struct FMicronClass
	{
		class_id ID;
		real_t Score;
	} FMicronClass;

	typedef struct FMicronProfile
	{
		size_t Size;
		FMicronClass* List;
	} FMicronProfile;

	typedef struct FMicronTrace
	{
		size_t Size;
		FMicronShape* Sequence;
	} FMicronTrace;

	typedef struct FMicronContact
	{
		micron_id MicronID;
		real_t Point, Weight;
	} FMicronContact;

	typedef struct FMicronFamily
	{
		size_t Size;
		FMicronContact* List;
	} FMicronFamily;

	typedef struct FMicron
	{
		micron_id ID;
		FMicronProfile Profile;
		FMicronTrace Trace;
		FMicronFamily Family;
	} FMicron;

	typedef struct FResult
	{
		size_t Size;
		FMicron* List;
		FPerformance Performance;
	} FResult;
}

