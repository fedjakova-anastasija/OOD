#include "stdafx.h"
#include "HarmonicOscillationsGroup.h"
#include "HarmonicOscillations.h"

double HarmonicOscillationsGroup::CalculateValue(double x) const
{
	double calculatedValue = 0;

	for (auto& harmonic : m_harmonicOscillationsGroup)
	{
		calculatedValue += harmonic->CalculateValue(x);
	}

	return calculatedValue;
}

sig::connection HarmonicOscillationsGroup::DoOnHarmonicOscillationsChange(const HarmonicChangeSignal::slot_type& handler)
{
	return m_harmonicsUpdateSignal.connect(handler);
}

IHarmonic HarmonicOscillationsGroup::GetHarmonicOscillations(size_t index) const
{
	if (index < m_harmonicOscillationsGroup.size())
	{
		return m_harmonicOscillationsGroup[index];
	}
	else
	{
		throw std::out_of_range("Wrong index!");
	}
}

size_t HarmonicOscillationsGroup::GetHarmonicsCount() const
{
	return m_harmonicOscillationsGroup.size();
}

void HarmonicOscillationsGroup::AddNewHarmonicOscillations(HarmonicOscillationTypes harmonicOscillationsType, double amplitude, double frequency, double phase)
{
	auto harmonic = std::make_shared<HarmonicOscillations>(harmonicOscillationsType, amplitude, frequency, phase);
	m_harmonicOscillationsGroup.push_back(harmonic);
	m_harmonicsUpdateSignal();
}

void HarmonicOscillationsGroup::DeleteHarmonicOscillations(size_t index)
{
	if (index < m_harmonicOscillationsGroup.size())
	{
		m_harmonicOscillationsGroup.erase(m_harmonicOscillationsGroup.begin() + index);
		m_harmonicsUpdateSignal();
	}
	else
	{
		throw std::out_of_range("Wrong index!");
	}
}
