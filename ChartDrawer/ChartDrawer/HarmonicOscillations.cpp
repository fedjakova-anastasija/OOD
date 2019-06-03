#include "stdafx.h"
#include "HarmonicOscillations.h"

HarmonicOscillations::HarmonicOscillations(HarmonicOscillationTypes harmonicOscillationsType, double amplitude, double frequency, double phase)
	: m_amplitude(amplitude)
	, m_frequency(frequency)
	, m_phase(phase)
	, m_harmonicOscillationsType(harmonicOscillationsType)
{
}

double HarmonicOscillations::CalculateValue(double x) const
{
	auto function = std::sinl;
	if (m_harmonicOscillationsType == HarmonicOscillationTypes::Cos)
	{
		function = std::cosl;
	}

	auto calculatedValue = m_amplitude * function(m_frequency * x + m_phase);
	return calculatedValue;
}

sig::connection HarmonicOscillations::DoOnHarmonicOscillationsChange(const HarmonicOscillationsChangeSignal::slot_type& handler)
{
	return m_harmonicOscillationsChanged.connect(handler);
}

HarmonicOscillationTypes HarmonicOscillations::GetHarmonicOscillationsType() const
{
	return m_harmonicOscillationsType;
}

void HarmonicOscillations::SetHarmonicOscillationsType(HarmonicOscillationTypes harmonicOscillationsType)
{
	m_harmonicOscillationsType = harmonicOscillationsType;
	m_harmonicOscillationsChanged();
}

double HarmonicOscillations::GetAmplitude() const
{
	return m_amplitude;
}

void HarmonicOscillations::SetAmplitude(double amplitude)
{
	m_amplitude = amplitude;
	m_harmonicOscillationsChanged();
}

double HarmonicOscillations::GetFrequency() const
{
	return m_frequency;
}

void HarmonicOscillations::SetFrequency(double frequency)
{
	m_frequency = frequency;
	m_harmonicOscillationsChanged();
}

double HarmonicOscillations::GetPhase() const
{
	return m_phase;
}

void HarmonicOscillations::SetPhase(double phase)
{
	m_phase = phase;
	m_harmonicOscillationsChanged();
}