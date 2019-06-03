// MainDlg.h : header file
//
#pragma once

#include "IMainDlgView.h"
#include "ChartView.h"

class MainDlg
	: public CDialogEx
	, public IMainDlgView
{
public:
	MainDlg(CWnd* pParent = NULL); // standard constructor

#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_DIALOG1
	};
#endif

	void SetHarmonicOscillationsParams(double amplitude, double frequency, double phase) final;
	void AddHarmonicOscillationsToGroup(Group const& harmonicOscillationsGroup) override final;
	void InitDefaultHarmonicOscillations() override final;
	void UpdateInputFields(HarmonicOscillationTypes harmonicOscillationType, double amplitude, double frequency, double phase) override final;
	IChartView& GetChartView() final;
	CListBox m_harmonicOscillationsGroup;
	CButton m_buttonSin;
	CButton m_buttonCos;
	CButton m_buttonAdd;
	CButton m_buttonDelete;
	CEdit m_amplitude;
	CEdit m_frequency;
	CEdit m_phase;

	sig::connection DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnHarmonicOscillationsTypeChange(const HarmonicOscillationsTypeChangeSignal::slot_type& handler) final;
	sig::connection DoOnAddHarmonicOscillations(const HarmonicOscillationsAddSignal::slot_type& handler) final;
	sig::connection DoOnDeleteHarmonicOscillations(const HarmonicOscillationsDeleteSignal::slot_type& handler) final;
	sig::connection DoOnInit(const InitSignal::slot_type& handler) final;
	sig::connection DoOnSetGroup(const HarmonicOscillationsChangeSignal::slot_type& handler) final;

protected:
	BOOL PreTranslateMessage(MSG* msg) override;
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	// Implementation
private:
	void OnChangeAmplitude();
	void OnChangeFrequency();
	void OnChangePhase();

	void OnOK() final;

	afx_msg void OnKillfocusAmplitude();
	afx_msg void OnKillfocusFrequency();
	afx_msg void OnKillfocusPhase();
	afx_msg void OnClickedRadioSin();
	afx_msg void OnClickedRadioCos();
	afx_msg void OnClickedAddHarmonic();
	afx_msg void OnClickedDeleteHarmonic();
	afx_msg void OnSetFocusGroup();

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	HarmonicCoeffChangeSignal m_amplitudeChanged;
	HarmonicCoeffChangeSignal m_frequencyChanged;
	HarmonicCoeffChangeSignal m_phaseChanged;
	HarmonicOscillationsTypeChangeSignal m_typeChanged;
	HarmonicOscillationsAddSignal m_addHarmonic;
	HarmonicOscillationsDeleteSignal m_deleteHarmonic;
	HarmonicOscillationsChangeSignal m_setFocusGroup;
	InitSignal m_init;

	float GetHarmonicCoeffValue(CEdit & coef);

private:
	ChartView m_chart;
};
