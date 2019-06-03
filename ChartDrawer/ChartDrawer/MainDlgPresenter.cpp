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
	m_view.DoOnHarmonicOscillationsTypeChange(std::bind(&MainDlgPresenter::SetHarmonicOscillationsType, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnAddHarmonicOscillations(std::bind(&MainDlgPresenter::AddHarmonicOscillations, this));
	m_view.DoOnDeleteHarmonicOscillations(std::bind(&MainDlgPresenter::DeleteHarmonicOscillations, this, std::placeholders::_1));
	m_view.DoOnSetGroup(std::bind(&MainDlgPresenter::SetFocusListBox, this, std::placeholders::_1));
	m_view.DoOnInit(std::bind(&MainDlgPresenter::InitView, this));
	m_harmonicOscillationsGroup.DoOnHarmonicOscillationsChange([this] {
		Update();
	});
}

void MainDlgPresenter::SetAmplitude(int index, double value)
{
	m_harmonicOscillationsGroup.GetHarmonicOscillations(index)->SetAmplitude(value);
}

void MainDlgPresenter::SetFrequency(int index, double value)
{
	m_harmonicOscillationsGroup.GetHarmonicOscillations(index)->SetFrequency(value);
}

void MainDlgPresenter::SetPhase(int index, double value)
{
	m_harmonicOscillationsGroup.GetHarmonicOscillations(index)->SetPhase(value);
}

void MainDlgPresenter::SetHarmonicOscillationsType(int index, HarmonicOscillationTypes value)
{
	m_harmonicOscillationsGroup.GetHarmonicOscillations(index)->SetHarmonicOscillationsType(value);
}

void MainDlgPresenter::InitView()
{
	Update();
	m_harmonicOscillationsGroup.AddNewHarmonicOscillations(HarmonicOscillationTypes::Sin, 0, 0, 0);
	m_harmonicOscillationsGroup.GetHarmonicOscillations(m_harmonicOscillationsGroup.GetHarmonicsCount() - 1)
		->DoOnHarmonicOscillationsChange(std::bind(&MainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonicOscillations();
	m_view.UpdateInputFields(HarmonicOscillationTypes::Sin, 0, 0, 0);
}

void MainDlgPresenter::Update()
{
	UpdateGroup();
	UpdateChart();
}

void MainDlgPresenter::AddHarmonicOscillations()
{

	m_harmonicOscillationsGroup.AddNewHarmonicOscillations(HarmonicOscillationTypes::Sin, 0, 0, 0);
	m_harmonicOscillationsGroup.GetHarmonicOscillations(m_harmonicOscillationsGroup.GetHarmonicsCount() - 1)
		->DoOnHarmonicOscillationsChange(std::bind(&MainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonicOscillations();
	m_view.UpdateInputFields(HarmonicOscillationTypes::Sin, 0, 0, 0);
}

void MainDlgPresenter::DeleteHarmonicOscillations(int index)
{
	m_harmonicOscillationsGroup.DeleteHarmonicOscillations(index);
}

void MainDlgPresenter::SetFocusListBox(int index)
{
	auto harmonic = m_harmonicOscillationsGroup.GetHarmonicOscillations(index);
	m_view.UpdateInputFields(harmonic->GetHarmonicOscillationsType(), harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase());
}

void MainDlgPresenter::UpdateGroup()
{
	ListBox harmonics;

	for (size_t i = 0; i < m_harmonicOscillationsGroup.GetHarmonicsCount(); ++i)
	{
		auto harmonic = m_harmonicOscillationsGroup.GetHarmonicOscillations(i);

		auto amplitude = harmonic->GetAmplitude();
		auto frequency = harmonic->GetFrequency();
		auto phase = harmonic->GetPhase();
		auto type = harmonic->GetHarmonicOscillationsType();

		std::string typeStr = ToString(type);

		auto strm = (boost::wformat(L"%1% * %2%(%3%x + %4%)") % amplitude % typeStr.c_str() % frequency % phase).str();
		harmonics.push_back(strm.c_str());
	}

	m_view.AddHarmonicOscillationsToGroup(harmonics);
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