#pragma once
#include "HarmonicOscillationTypes.h"
#include "Signals.h"

class HarmonicOscillations
{
public:
	HarmonicOscillations(HarmonicOscillationTypes harmonicOscillationType, double amplitude, double frequency, double phase);
	~HarmonicOscillations() {};

	typedef sig::signal<void()> HarmonicOscillationsChangeSignal;
	sig::connection DoOnHarmonicOscillationsChange(const HarmonicOscillationsChangeSignal::slot_type& handler);
	
	double GetAmplitude() const;
	void SetAmplitude(double amplitude);

	double GetFrequency() const;
	void SetFrequency(double frequency);

	double GetPhase() const;
	void SetPhase(double phase);
	
	double CalculateValue(double x) const;
	HarmonicOscillationTypes GetHarmonicOscillationsType() const;
	void SetHarmonicOscillationsType(HarmonicOscillationTypes harmonicOscillationsType);

private:
	double m_amplitude;
	double m_frequency;
	double m_phase;

	HarmonicOscillationTypes m_harmonicOscillationsType;
	HarmonicOscillationsChangeSignal m_harmonicOscillationsChanged;
};