//#pragma once
//#include "stdafx.h"
//#include "HarmonicOscillationTypes.h"
//#include "Signals.h"
//
//class IHarmonicOscillation
//{
//public:
//	virtual ~IHarmonicOscillation() = default;
//
//	virtual double CalculateValue(double x) const = 0;
//
//	typedef sig::signal<void()> HarmonicChangeSignal;
//
//	virtual sig::connection DoOnHarmonicChange(const HarmonicChangeSignal::slot_type& handler) = 0;
//
//	virtual double GetAmplitude() const = 0;
//	virtual void SetAmplitude(double amplitude) = 0;
//
//	virtual double GetFrequency() const = 0;
//	virtual void SetFrequency(double frequency) = 0;
//
//	virtual double GetPhase() const = 0;
//	virtual void SetPhase(double phase) = 0;
//
//	virtual HarmonicOscillationTypes GetHarmonicType() const = 0;
//	virtual void SetHarmonicType(HarmonicOscillationTypes type) = 0;	
//};
