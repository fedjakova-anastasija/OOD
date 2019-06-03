#include "stdafx.h"
#include "MainDlgPresenter.h"
#include "AddHarmonicDlgPresenter.h"
#include "AddHarmonicView.h"
#include "HarmonicOscillationTypes.h"
#include "IChartView.h"
#include "IHarmonicOscillationGroup.h"
#include "IMainDlgView.h"

MainDlgPresenter::MainDlgPresenter(HarmonicOscillationsGroup& harmonicOscillationsGroup, IMainDlgView& view)
	: m_harmonicOscillationsGroup(harmonicOscillationsGroup)
	, m_view(view)
{
	m_view.DoOnAmplitudeChange(std::bind(&MainDlgPresenter::SetAmplitude, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnFrequencyChange(std::bind(&MainDlgPresenter::SetFrequency, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnPhaseChange(std::bind(&MainDlgPresenter::SetPhase, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnHarmonicTypeChange(std::bind(&MainDlgPresenter::SetHarmonicType, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnAddHarmonic(std::bind(&MainDlgPresenter::AddHarmonic, this));
	m_view.DoOnDeleteHarmonic(std::bind(&MainDlgPresenter::DeleteHarmonic, this, std::placeholders::_1));
	m_view.DoOnSetFocusListBox(std::bind(&MainDlgPresenter::SetFocusListBox, this, std::placeholders::_1));
	m_view.DoOnInit(std::bind(&MainDlgPresenter::InitView, this));
	m_harmonicOscillationsGroup.DoOnHarmonicOscillationsChange([this] {
		Update();
	});
}

void MainDlgPresenter::SetAmplitude(int index, double value)
{
	m_harmonicOscillationsGroup.GetHarmonic(index)->SetAmplitude(value);
}

void MainDlgPresenter::SetFrequency(int index, double value)
{
	m_harmonicOscillationsGroup.GetHarmonic(index)->SetFrequency(value);
}

void MainDlgPresenter::SetPhase(int index, double value)
{
	m_harmonicOscillationsGroup.GetHarmonic(index)->SetPhase(value);
}

void MainDlgPresenter::SetHarmonicType(int index, HarmonicOscillationTypes value)
{
	m_harmonicOscillationsGroup.GetHarmonic(index)->SetHarmonicOscillationsType(value);
}

void MainDlgPresenter::InitView()
{
	Update();
	m_harmonicOscillationsGroup.AddNewHarmonic(HarmonicOscillationTypes::Sin, 0, 0, 0);
	m_harmonicOscillationsGroup.GetHarmonic(m_harmonicOscillationsGroup.GetHarmonicsCount() - 1)
		->DoOnHarmonicOscillationsChange(std::bind(&MainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonic();
	m_view.UpdateInputFields(HarmonicOscillationTypes::Sin, 0, 0, 0);
}

void MainDlgPresenter::Update()
{
	UpdateGroup();
	UpdateChart();
}

void MainDlgPresenter::AddHarmonic()
{

	m_harmonicOscillationsGroup.AddNewHarmonic(HarmonicOscillationTypes::Sin, 0, 0, 0);
	m_harmonicOscillationsGroup.GetHarmonic(m_harmonicOscillationsGroup.GetHarmonicsCount() - 1)
		->DoOnHarmonicOscillationsChange(std::bind(&MainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonic();
	m_view.UpdateInputFields(HarmonicOscillationTypes::Sin, 0, 0, 0);
}

void MainDlgPresenter::DeleteHarmonic(int index)
{
	m_harmonicOscillationsGroup.DeleteHarmonic(index);
}

void MainDlgPresenter::SetFocusListBox(int index)
{
	auto harmonic = m_harmonicOscillationsGroup.GetHarmonic(index);
	m_view.UpdateInputFields(harmonic->GetHarmonicOscillationsType(), harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase());
}

void MainDlgPresenter::UpdateGroup()
{
	ListBox harmonics;

	for (size_t i = 0; i < m_harmonicOscillationsGroup.GetHarmonicsCount(); ++i)
	{
		auto harmonic = m_harmonicOscillationsGroup.GetHarmonic(i);

		auto amplitude = harmonic->GetAmplitude();
		auto frequency = harmonic->GetFrequency();
		auto phase = harmonic->GetPhase();
		auto type = harmonic->GetHarmonicOscillationsType();

		std::string typeStr = ToString(type);

		auto strm = (boost::wformat(L"%1% * %2%(%3%x + %4%)") % amplitude % typeStr.c_str() % frequency % phase).str();
		harmonics.push_back(strm.c_str());
	}

	m_view.AddHarmonicsToListBox(harmonics);
}

void MainDlgPresenter::UpdateChart()
{
	IChartView::Points2D points;
	for (double x = -10.0; x <= +10; x += 0.1)
	{
		points.emplace_back(x, m_harmonicOscillationsGroup.CalculateValue(x));
	}
	m_view.GetChartView().SetData(points);
}