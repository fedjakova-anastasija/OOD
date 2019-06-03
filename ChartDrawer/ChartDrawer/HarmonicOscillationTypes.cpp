#include "stdafx.h"
#include "HarmonicOscillationTypes.h"

std::string ToString(HarmonicOscillationTypes harmonicOscillationType)
{
	std::string harmonicOscillationTypeStr = "sin";
	if (harmonicOscillationType == HarmonicOscillationTypes::Cos)
	{
		harmonicOscillationTypeStr = "cos";
	}

	return harmonicOscillationTypeStr;
}