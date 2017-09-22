#pragma once

#include "MicronML_Types.h"

namespace MicronML
{
	namespace PEdgeProfile
	{
		typedef struct FKernel
		{
			size_t Size;
			real_t Norm;
			real_t* Weights;
		} FKernel;

		typedef FKernel FWavelet;
	}
}