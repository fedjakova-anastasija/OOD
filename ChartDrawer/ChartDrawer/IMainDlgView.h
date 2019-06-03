#pragma once

#include "HarmonicOscillationTypes.h"
#include "Signals.h"

class IChartView;

class IMainDlgView
{
public:
	typedef sig::signal<void(int value1, float value2)> HarmonicCoeffChangeSignal;
	typedef sig::signal<void(int value1, HarmonicOscillationTypes value2)> HarmonicOscillationsTypeChangeSignal;
	typedef sig::signal<void()> HarmonicOscillationsAddSignal;
	typedef sig::signal<void(int value1)> HarmonicOscillationsDeleteSignal;
	typedef sig::signal<void(int value1)> HarmonicOscillationsChangeSignal;

	typedef sig::signal<void()> InitSignal;
	typedef std::vector<std::wstring> Group;

	virtual IChartView& GetChartView() = 0;
	virtual void AddHarmonicOscillationsToGroup(Group const& group) = 0;
	virtual void InitDefaultHarmonicOscillations() = 0;
	virtual void UpdateInputFields(HarmonicOscillationTypes harmonicOscillationType, double amplitude, double frequency, double phase) = 0;

	virtual void SetHarmonicOscillationsParams(double a, double b, double c) = 0;

	// Signals
	virtual sig::connection DoOnInit(const InitSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnHarmonicOscillationsTypeChange(const HarmonicOscillationsTypeChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnAddHarmonicOscillations(const HarmonicOscillationsAddSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnDeleteHarmonicOscillations(const HarmonicOscillationsDeleteSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnSetGroup(const HarmonicOscillationsChangeSignal::slot_type& handler) = 0;

	virtual ~IMainDlgView() = default;
};
