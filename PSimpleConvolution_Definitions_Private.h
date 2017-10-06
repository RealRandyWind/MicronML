#pragma once

#include "MicronML_Types.h"

namespace MicronML
{
	namespace PSimpleConvolution
	{
		typedef struct FNeuron
		{
			size_t Size;
			real_t* Weights;
		} FNeuron;

		typedef struct FLayer
		{
			real_t Bias;
			size_t Size;
			FNeuron* Neurons;
		} FLayer;

		typedef struct FNetwork
		{
			size_t Size;
			size_t MaximumLayerSize;
			FLayer* Layers;
		} FNetwork;

		typedef struct FCharge
		{
			size_t Size;
			real_t* Values;
		} FCharge;

	}
}