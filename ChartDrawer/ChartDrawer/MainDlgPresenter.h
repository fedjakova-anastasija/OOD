#pragma once
#include "HarmonicOscillationTypes.h"
#include "HarmonicOscillationsGroup.h"

class IMainDlgView;

class MainDlgPresenter
{
public:
	typedef std::vector<std::wstring> ListBox;

	MainDlgPresenter(HarmonicOscillationsGroup& harmonicOscillationsGroup, IMainDlgView& view);

private:
	void InitView();
	void UpdateGroup();
	void UpdateChart();

	void SetFocusListBox(int index);
	void SetAmplitude(int index, double value);
	void SetFrequency(int index, double value);
	void SetPhase(int index, double value);
	void SetHarmonicType(int index, HarmonicOscillationTypes value);
	void AddHarmonic();
	void DeleteHarmonic(int index);
	void Update();

	HarmonicOscillationsGroup& m_harmonicOscillationsGroup;
	IMainDlgView& m_view;
};
