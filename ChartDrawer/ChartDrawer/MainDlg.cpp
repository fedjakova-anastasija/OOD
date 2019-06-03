
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

BOOL MainDlg::PreTranslateMessage(MSG* msg)
{
	if (msg->message == WM_KEYDOWN && msg->wParam == VK_RETURN)
	{
		auto focus = GetFocus();
		if (focus == GetDlgItem(IDC_AMPLITUDE_FIELD))
		{
			OnChangeAmplitude();
			return TRUE;
		}
		else if (focus == GetDlgItem(IDC_FREQUENCE_FIELD))
		{
			OnChangeFrequency();
			return TRUE;
		}
		else if (focus == GetDlgItem(IDC_PHASE_FIELD))
		{
			OnChangePhase();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(msg);
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AMPLITUDE_FIELD, m_amplitude);
	DDX_Control(pDX, IDC_HARMONICS_GROUP, m_harmonicOscillationsGroup);
	DDX_Control(pDX, IDC_CHECKBOX_SIN, m_buttonSin);
	DDX_Control(pDX, IDC_CHECKBOX_COS, m_buttonCos);
	DDX_Control(pDX, IDC_BUTTON_ADD_NEW_HARMONIC, m_buttonAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE_HARMONIC, m_buttonDelete);
	DDX_Control(pDX, IDC_FREQUENCE_FIELD, m_frequency);
	DDX_Control(pDX, IDC_PHASE_FIELD, m_phase);
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_AMPLITUDE_FIELD, &MainDlg::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE_FIELD, &MainDlg::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE_FIELD, &MainDlg::OnKillfocusPhase)
	ON_BN_CLICKED(IDC_CHECKBOX_SIN, &MainDlg::OnClickedRadioSin)
	ON_BN_CLICKED(IDC_CHECKBOX_COS, &MainDlg::OnClickedRadioCos)
	ON_BN_CLICKED(IDC_BUTTON_ADD_NEW_HARMONIC, &MainDlg::OnClickedAddHarmonic)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_HARMONIC, &MainDlg::OnClickedDeleteHarmonic)
	ON_LBN_SELCHANGE(IDC_HARMONICS_GROUP, &MainDlg::OnSetFocusListBox)
END_MESSAGE_MAP()

BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	m_chart.SubclassDlgItem(IDC_GRAPH, this);
	GetDlgItem(IDC_BUTTON_DELETE_HARMONIC)->EnableWindow(false);

	m_init();

	return TRUE; // return TRUE  unless you set the focus to a control
}

void MainDlg::SetHarmonicOscillationsParams(double amplitude, double frequency, double phase)
{
	m_amplitude.SetWindowTextW((boost::wformat(L"%1%") % amplitude).str().c_str());
	m_frequency.SetWindowTextW((boost::wformat(L"%1%") % frequency).str().c_str());
	m_phase.SetWindowTextW((boost::wformat(L"%1%") % phase).str().c_str());
	if (m_hWnd)
	{
		UpdateData(FALSE);
	}
}

sig::connection MainDlg::DoOnInit(const InitSignal::slot_type& handler)
{
	return m_init.connect(handler);
	GetDlgItem(IDC_GRAPH)->ShowWindow(true);
}

void MainDlg::InitDefaultHarmonicOscillations()
{
	int num = m_harmonicOscillationsGroup.GetCount() - 1;
	m_harmonicOscillationsGroup.SetCurSel(num);
	m_buttonSin.SetCheck(1);
	m_buttonCos.SetCheck(0);
	GetDlgItem(IDC_BUTTON_DELETE_HARMONIC)->EnableWindow(true);
	GetDlgItem(IDC_AMPLITUDE_FIELD)->EnableWindow(true);
	GetDlgItem(IDC_FREQUENCE_FIELD)->EnableWindow(true);
	GetDlgItem(IDC_PHASE_FIELD)->EnableWindow(true);
	GetDlgItem(IDC_CHECKBOX_SIN)->EnableWindow(true);
	GetDlgItem(IDC_CHECKBOX_COS)->EnableWindow(true);
}

void MainDlg::UpdateInputFields(HarmonicOscillationTypes harmonicOscillationTypes, double amplitude, double frequency, double phase)
{
	int index = m_harmonicOscillationsGroup.GetCurSel();
	if (index >= 0)
	{
		m_amplitude.SetWindowTextW((boost::wformat(L"%1%") % amplitude).str().c_str());
		m_frequency.SetWindowTextW((boost::wformat(L"%1%") % frequency).str().c_str());
		m_phase.SetWindowTextW((boost::wformat(L"%1%") % phase).str().c_str());

		auto functionType = IDC_CHECKBOX_SIN;
		if (harmonicOscillationTypes == HarmonicOscillationTypes::Sin)
		{
			functionType = IDC_CHECKBOX_COS;
		}

		CheckRadioButton(IDC_CHECKBOX_SIN, IDC_CHECKBOX_COS, functionType);
	}
}

IChartView& MainDlg::GetChartView()
{
	return m_chart;
}

sig::connection MainDlg::DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_amplitudeChanged.connect(handler);
}

sig::connection MainDlg::DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_frequencyChanged.connect(handler);
}

sig::connection MainDlg::DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_phaseChanged.connect(handler);
}

sig::connection MainDlg::DoOnHarmonicOscillationsTypeChange(const HarmonicOscillationsTypeChangeSignal::slot_type& handler)
{
	return m_typeChanged.connect(handler);
}

sig::connection MainDlg::DoOnAddHarmonicOscillations(const HarmonicOscillationsAddSignal::slot_type& handler)
{
	return m_addHarmonic.connect(handler);
}

sig::connection MainDlg::DoOnDeleteHarmonicOscillations(const HarmonicOscillationsDeleteSignal::slot_type& handler)
{
	return m_deleteHarmonic.connect(handler);
}

sig::connection MainDlg::DoOnSetGroup(const HarmonicOscillationsChangeSignal::slot_type& handler)
{
	return m_setFocusList.connect(handler);
}

float MainDlg::GetHarmonicCoeffValue(CEdit & coef)
{
	CString val;
	coef.GetWindowTextW(val);
	return boost::lexical_cast<float>(val.GetBuffer());
}

void MainDlg::OnChangeAmplitude()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_amplitudeChanged(index, GetHarmonicCoeffValue(m_amplitude));
			m_harmonicOscillationsGroup.SetCurSel(index); 
		}
	}
}

void MainDlg::OnChangeFrequency()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_frequencyChanged(index, GetHarmonicCoeffValue(m_frequency));
			m_harmonicOscillationsGroup.SetCurSel(index);
		}
	}
}

void MainDlg::OnChangePhase()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_phaseChanged(index, GetHarmonicCoeffValue(m_phase));
			m_harmonicOscillationsGroup.SetCurSel(index);
		}
	}
}

void MainDlg::OnOK()
{
}

void MainDlg::OnKillfocusAmplitude()
{
	OnChangeAmplitude();
}

void MainDlg::OnClickedRadioSin()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_typeChanged(index, HarmonicOscillationTypes::Sin);
			m_harmonicOscillationsGroup.SetCurSel(index);
		}
	}
}

void MainDlg::OnClickedRadioCos()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_typeChanged(index, HarmonicOscillationTypes::Cos);
			m_harmonicOscillationsGroup.SetCurSel(index);
		}
	}
}

void MainDlg::OnClickedAddHarmonic()
{
	if (UpdateData())
	{
		m_addHarmonic();
		int index = m_harmonicOscillationsGroup.GetCount() - 1;
		m_harmonicOscillationsGroup.SetCurSel(index);
	}
}

void MainDlg::OnSetFocusListBox()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_setFocusList(index);
		}
	}
}

void MainDlg::OnClickedDeleteHarmonic()
{
	if (UpdateData())
	{
		int index = m_harmonicOscillationsGroup.GetCurSel();
		if (index >= 0)
		{
			m_deleteHarmonic(index);
			if (m_harmonicOscillationsGroup.GetCount() == 0)
			{
				GetDlgItem(IDC_BUTTON_DELETE_HARMONIC)->EnableWindow(false);
				GetDlgItem(IDC_AMPLITUDE_FIELD)->EnableWindow(false);
				GetDlgItem(IDC_FREQUENCE_FIELD)->EnableWindow(false);
				GetDlgItem(IDC_PHASE_FIELD)->EnableWindow(false);
				GetDlgItem(IDC_CHECKBOX_SIN)->EnableWindow(false);
				GetDlgItem(IDC_CHECKBOX_COS)->EnableWindow(false);
			}
			else
			{
				m_harmonicOscillationsGroup.SetCurSel((m_harmonicOscillationsGroup.GetCount() - 1 >= index ? index : index - 1));
			}
		}
	}
}

void MainDlg::OnKillfocusFrequency()
{
	OnChangeFrequency();
}

void MainDlg::OnKillfocusPhase()
{
	OnChangePhase();
}

void MainDlg::AddHarmonicOscillationsToGroup(Group const& harmonicOscillationsGroup)
{
	m_harmonicOscillationsGroup.ResetContent();

	for (auto& str : harmonicOscillationsGroup)
	{
		m_harmonicOscillationsGroup.AddString(str.c_str());
	}
}
