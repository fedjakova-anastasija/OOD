#include "stdafx.h"
//#include "AddHarmonicDlgPresenter.h"
//#include "HarmonicOscillationTypes.h"
////#include "IChartView.h"
////#include "IHarmonicCollection.h"
//#include "IAddHarmonicView.h"
//
//AddHarmonicDlgPresenter::AddHarmonicDlgPresenter()
//{
//	/*m_view.DoOnAmplitudeChange(std::bind(&AddHarmonicDlgPresenter::SetAmplitude, this, std::placeholders::_1, std::placeholders::_2));
//	m_view.DoOnFrequencyChange(std::bind(&AddHarmonicDlgPresenter::SetFrequency, this, std::placeholders::_1, std::placeholders::_2));
//	m_view.DoOnPhaseChange(std::bind(&AddHarmonicDlgPresenter::SetPhase, this, std::placeholders::_1, std::placeholders::_2));
//	m_view.DoOnHarmonicTypeChange(std::bind(&AddHarmonicDlgPresenter::SetHarmonicType, this, std::placeholders::_1, std::placeholders::_2));
//	m_view.DoOnAddHarmonic(std::bind(&AddHarmonicDlgPresenter::AddHarmonic, this));
//	m_view.DoOnDeleteHarmonic(std::bind(&AddHarmonicDlgPresenter::DeleteHarmonic, this, std::placeholders::_1));
//	m_view.DoOnSetFocusListBox(std::bind(&AddHarmonicDlgPresenter::SetFocusListBox, this, std::placeholders::_1));*/
//	//m_view.DoOnInit(std::bind(&AddHarmonicDlgPresenter::InitView, this));
//	//m_view = new AddHarmonicView();
//	/*m_collection.DoOnHarmonicChange([this] {
//	Update();
//	});*/
//}
//
////void AddHarmonicDlgPresenter::SetAmplitude(int index, double value)
////{
////	m_collection.GetHarmonic(index)->SetAmplitude(value);
////}
////
////void AddHarmonicDlgPresenter::SetFrequency(int index, double value)
////{
////	m_collection.GetHarmonic(index)->SetFrequency(value);
////}
////
////void AddHarmonicDlgPresenter::SetPhase(int index, double value)
////{
////	m_collection.GetHarmonic(index)->SetPhase(value);
////}
////
////void AddHarmonicDlgPresenter::SetHarmonicType(int index, HarmonicType value)
////{
////	m_collection.GetHarmonic(index)->SetHarmonicType(value);
////}
////
////void AddHarmonicDlgPresenter::InitView()
////{
////	m_view.ShowWindow();
////}
////
////void AddHarmonicDlgPresenter::Update()
////{
////	UpdateHarmonicsList();
////	//UpdateTable(); TODO::update table
////	UpdateChart();
////}
////
////void AddHarmonicDlgPresenter::AddHarmonic()
////{
////	m_collection.AddHarmonic(1, 1, 0, HarmonicType::Sin);
////	m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
////		->DoOnHarmonicChange(std::bind(&AddHarmonicDlgPresenter::Update, this));
////	m_view.InitDefaultHarmonic();
////	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);
////}
////
////void AddHarmonicDlgPresenter::DeleteHarmonic(int index)
////{
////	m_collection.DeleteHarmonic(index);
////}
////
////void AddHarmonicDlgPresenter::SetFocusListBox(int index)
////{
////	auto harmonic = m_collection.GetHarmonic(index);
////	m_view.UpdateFields(harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase(), harmonic->GetHarmonicType()); //TODO:: реализовать метод, обновл€ющий пол€
////} 
////
////void AddHarmonicDlgPresenter::UpdateHarmonicsList()
////{
////	ListBox harmonics;
////
////	for (size_t i = 0; i < m_collection.GetHarmonicsCount(); ++i)
////	{
////		auto harmonic = m_collection.GetHarmonic(i);
////
////		auto amplitude = harmonic->GetAmplitude();
////		auto frequency = harmonic->GetFrequency();
////		auto phase = harmonic->GetPhase();
////		auto type = harmonic->GetHarmonicType();
////
////		std::string typeStr = (type == HarmonicType::Sin) ? "sin" : "cos";
////
////		auto strm = (boost::wformat(L"%1% * %2%(%3%x + %4%)") % amplitude % typeStr.c_str() % frequency % phase).str();
////		harmonics.push_back(strm.c_str());
////	}
////
////	m_view.AddHarmonicsToListBox(harmonics);
////}
////
////void AddHarmonicDlgPresenter::UpdateChart()
////{
////	IChartView::Points2D points;
////	for (double x = -10.0; x <= +10; x += 0.1)
////	{
////		points.emplace_back(x, m_collection.CalculateValue(x));
////	}
////	m_view.GetChartView().SetData(points);
////}
//