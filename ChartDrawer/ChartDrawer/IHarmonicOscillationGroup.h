//#pragma once
//#include "stdafx.h"
//#include "IHarmonicOscillation.h"
//#include "HarmonicOscillations.h"
//
//typedef std::shared_ptr<HarmonicOscillations> IHarmonicPointer;
//
//class IHarmonicOscillationGroup
//{
//public:
//
//	typedef sig::signal<void()> HarmonicChangeSignal;
//
//	virtual ~IHarmonicOscillationGroup() = default;
//
//	virtual double CalculateValue(double x) const = 0;
//
//	virtual sig::connection DoOnHarmonicChange(const HarmonicChangeSignal::slot_type& handler) = 0;
//
//	virtual IHarmonicPointer GetHarmonic(size_t index) const = 0;
//	virtual void AddHarmonic(double aplitude, double frequency, double phase, HarmonicOscillationTypes type) = 0;
//	virtual void DeleteHarmonic(size_t index) = 0;
//	virtual size_t GetHarmonicsCount() const = 0;
//};
