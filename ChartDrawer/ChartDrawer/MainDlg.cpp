
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
		if (focus == GetDlgItem(IDC_AMPLITUDE))
		{
			OnChangeAmplitude();
			return TRUE;
		}
		else if (focus == GetDlgItem(IDC_FREQUENCE))
		{
			OnChangeFrequency();
			return TRUE;
		}
		else if (focus == GetDlgItem(IDC_PHASE))
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
	DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Control(pDX, IDC_HARMONICS_LISTBOX, m_harmonicsList);
	DDX_Control(pDX, IDC_RADIO_SIN, m_buttonSin);
	DDX_Control(pDX, IDC_RADIO_COS, m_buttonCos);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Control(pDX, IDC_FREQUENCE, m_frequency);
	DDX_Control(pDX, IDC_PHASE, m_phase);
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_AMPLITUDE, &MainDlg::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE, &MainDlg::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE, &MainDlg::OnKillfocusPhase)
	ON_BN_CLICKED(IDC_RADIO_SIN, &MainDlg::OnClickedRadioSin)
	ON_BN_CLICKED(IDC_RADIO_COS, &MainDlg::OnClickedRadioCos)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &MainDlg::OnClickedAddHarmonic)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &MainDlg::OnClickedDeleteHarmonic)
	ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &MainDlg::OnSetFocusListBox)
END_MESSAGE_MAP()

BOOL MainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	m_chart.SubclassDlgItem(IDC_CHART, this);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(false);

	m_init();

	return TRUE; // return TRUE  unless you set the focus to a control
}

void MainDlg::SetHarmonicParams(double amplitude, double frequency, double phase)
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
	GetDlgItem(IDC_CHART)->ShowWindow(true);
}

void MainDlg::InitDefaultHarmonic()
{
	int num = m_harmonicsList.GetCount() - 1;
	m_harmonicsList.SetCurSel(num);
	m_buttonSin.SetCheck(1);
	m_buttonCos.SetCheck(0);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(true);
	GetDlgItem(IDC_AMPLITUDE)->EnableWindow(true);
	GetDlgItem(IDC_FREQUENCE)->EnableWindow(true);
	GetDlgItem(IDC_PHASE)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_SIN)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_COS)->EnableWindow(true);
}

void MainDlg::UpdateInputFields(HarmonicOscillationTypes harmonicOscillationTypes, double amplitude, double frequency, double phase)
{
	int index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_amplitude.SetWindowTextW((boost::wformat(L"%1%") % amplitude).str().c_str());
		m_frequency.SetWindowTextW((boost::wformat(L"%1%") % frequency).str().c_str());
		m_phase.SetWindowTextW((boost::wformat(L"%1%") % phase).str().c_str());

		auto functionType = IDC_RADIO_SIN;
		if (harmonicOscillationTypes == HarmonicOscillationTypes::Sin)
		{
			functionType = IDC_RADIO_COS;
		}

		CheckRadioButton(IDC_RADIO_SIN, IDC_RADIO_COS, functionType);
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

sig::connection MainDlg::DoOnHarmonicTypeChange(const HarmonicTypeChangeSignal::slot_type& handler)
{
	return m_typeChanged.connect(handler);
}

sig::connection MainDlg::DoOnAddHarmonic(const HarmonicAddSignal::slot_type& handler)
{
	return m_addHarmonic.connect(handler);
}

sig::connection MainDlg::DoOnDeleteHarmonic(const HarmonicDeleteSignal::slot_type& handler)
{
	return m_deleteHarmonic.connect(handler);
}

sig::connection MainDlg::DoOnSetFocusListBox(const HarmonicFocusListBoxChangeSignal::slot_type& handler)
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
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_amplitudeChanged(index, GetHarmonicCoeffValue(m_amplitude));
			m_harmonicsList.SetCurSel(index); 
		}
	}
}

void MainDlg::OnChangeFrequency()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_frequencyChanged(index, GetHarmonicCoeffValue(m_frequency));
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void MainDlg::OnChangePhase()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_phaseChanged(index, GetHarmonicCoeffValue(m_phase));
			m_harmonicsList.SetCurSel(index);
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
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_typeChanged(index, HarmonicOscillationTypes::Sin);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void MainDlg::OnClickedRadioCos()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_typeChanged(index, HarmonicOscillationTypes::Cos);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void MainDlg::OnClickedAddHarmonic()
{
	if (UpdateData())
	{
		m_addHarmonic();
		int index = m_harmonicsList.GetCount() - 1;
		m_harmonicsList.SetCurSel(index);
	}
}

void MainDlg::OnSetFocusListBox()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
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
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_deleteHarmonic(index);
			if (m_harmonicsList.GetCount() == 0)
			{
				GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(false);
				GetDlgItem(IDC_AMPLITUDE)->EnableWindow(false);
				GetDlgItem(IDC_FREQUENCE)->EnableWindow(false);
				GetDlgItem(IDC_PHASE)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_SIN)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_COS)->EnableWindow(false);
			}
			else
			{
				m_harmonicsList.SetCurSel((m_harmonicsList.GetCount() - 1 >= index ? index : index - 1));
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

void MainDlg::AddHarmonicsToListBox(ListBox const& harmonicsList)
{
	m_harmonicsList.ResetContent();

	for (auto& str : harmonicsList)
	{
		m_harmonicsList.AddString(str.c_str());
	}
}
