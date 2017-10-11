#pragma once

#include <stdint.h>

#define MicronML_Macro_Expand(Args) Args
#define MicronML_Macro_Concat(Left, Right) Left ## Right
#define MicronML_Macro_Select(Name, Count) MicronML_Macro_Concat( Name ## _, Count)
#define MicronML_Macro_Size(_1, _2, _3, _4, _5, _6, _7, _8, _9, Count, ...) Count
#define MicronML_Macro_Va_Size(...) MicronML_Macro_Expand(MicronML_Macro_Size(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define MicronML_Macro_Va_Select(Name, ...) MicronML_Macro_Expand(MicronML_Macro_Select(Name, MicronML_Macro_Va_Size(__VA_ARGS__))(__VA_ARGS__))

#define MicronML_NullCode 1
#define MicronML_NoneCode 1001
#define MicronML_FaildCode 2001
#define MicronML_InvalidCode 3001
#define MicronML_ActionCode 4001
#define MicronML_SpecialCode 5001
#define MicronML_OtherCode 6001

#define MicronML_None 0
#define MicronML_Null nullptr
#define MicronML_Default 0
#define MicronML_Success 0
#define MicronML_Unknown 0
#define MicronML_One 1
#define MicronML_First 0
#define MicronML_Second 0
#define MicronML_Zero 0
#define MicronML_NegOne -1
#define MicronML_OneF 1.0f
#define MicronML_ZeroF 0.0f
#define MicronML_NegOneF -1.0f
#define MicronML_Empty ""

#define MicronML_BaseBin 2
#define MicronML_BaseTer 3
#define MicronML_BaseOct 8
#define MicronML_BaseDec 10
#define MicronML_BaseHex 16

#define MicronML_ByteSize 8
#define MicronML_RawSize (sizeof(block_t) / sizeof(raw_t))
#define MicronML_RealSize (sizeof(block_t) / sizeof(real_t))

namespace MicronML
{
	typedef uint8_t raw_t;
	typedef uint32_t block_t;

	typedef float real_t;
	typedef bool bool_t;
	typedef int int_t;
	typedef size_t size_t;
	typedef char* string_t;
	typedef void* pointer_t;
	/*
	typedef uint64_t uuid_t;
	*/

	typedef size_t data_id;
	typedef size_t procedure_id;
	typedef size_t result_id;
	typedef size_t compound_id;

	typedef size_t micron_id;
	typedef size_t sample_id;
	typedef size_t shape_id;
	typedef size_t class_id;
	typedef size_t contact_id;

	typedef uint16_t enum_t;

	enum class EProcedureType : enum_t
	{
		None = MicronML_None,
		SimpleConvolution,
		DeepNeuralNetwork,
		TensorFlow,
		HistogramOrientedGradient,
		EdgeProfile,
		ArticleSolution,
		CurrentFix,
		RecurrentNeuralNetwork,
		_EnumSize
	};

}