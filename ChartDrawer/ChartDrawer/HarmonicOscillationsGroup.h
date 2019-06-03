#pragma once
#include "stdafx.h"
#include "IHarmonicOscillationGroup.h"
#include "HarmonicOscillations.h"
#include "Signals.h"

typedef std::shared_ptr<HarmonicOscillations> IHarmonic;

class HarmonicOscillationsGroup
{
public:
	HarmonicOscillationsGroup(){};
	~HarmonicOscillationsGroup(){};

	typedef sig::signal<void()> HarmonicChangeSignal;
	sig::connection DoOnHarmonicOscillationsChange(const HarmonicChangeSignal::slot_type& handler);

	IHarmonic GetHarmonicOscillations(size_t index) const;

	void AddNewHarmonicOscillations(HarmonicOscillationTypes harmonicOscillationsType, double amplitude, double frequency, double phase);
	void DeleteHarmonicOscillations(size_t index);
	
	double CalculateValue(double x) const;
	size_t GetHarmonicsCount() const;

private:
	std::vector<IHarmonic> m_harmonicOscillationsGroup;
	HarmonicChangeSignal m_harmonicsUpdateSignal;
};
