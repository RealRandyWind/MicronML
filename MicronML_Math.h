#pragma once

#include "MicronML_Types.h"

namespace MicronML
{
	inline real_t Abs(real_t Real) { return Real < MicronML_ZeroF ? -Real : Real; }
	inline real_t Sign(real_t Real) { return Real < MicronML_ZeroF ? MicronML_NegOneF : MicronML_OneF; }

}