#include "stdafx.h"
//#include "AddHarmonicView.h"
//#include "afxdialogex.h"
//#include "resource.h"
//#include "resource1.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
//
//AddHarmonicView::AddHarmonicView(CWnd* pParent /*=NULL*/)
//	: CDialogEx(IDD_ADD_NEW_HARMONIC_DIALOG, pParent)
//{
//	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
//}
//
//BOOL AddHarmonicView::PreTranslateMessage(MSG* msg)
//{
//	if (msg->message == WM_KEYDOWN && msg->wParam == VK_RETURN)
//	{
//		auto focus = GetFocus();
//		/*	if (focus == GetDlgItem(IDC_AMPLITUDE))
//		{
//		OnChangeAmplitude();
//		return TRUE;
//		}
//		else if (focus == GetDlgItem(IDC_FREQUENCE))
//		{
//		OnChangeFrequency();
//		return TRUE;
//		}
//		else if (focus == GetDlgItem(IDC_PHASE))
//		{
//		OnChangePhase();
//		return TRUE;
//		}*/
//	}
//	return CDialogEx::PreTranslateMessage(msg);
//}
//
//void AddHarmonicView::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//	/*DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude);
//	DDX_Control(pDX, IDC_HARMONICS_LISTBOX, m_harmonicsList);
//	DDX_Control(pDX, IDC_RADIO_SIN, m_buttonSin);
//	DDX_Control(pDX, IDC_RADIO_COS, m_buttonCos);
//	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
//	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
//	DDX_Control(pDX, IDC_FREQUENCE, m_frequency);
//	DDX_Control(pDX, IDC_PHASE, m_phase);*/
//}
//
////BEGIN_MESSAGE_MAP(AddHarmonicView, CDialogEx)
//	/*ON_EN_KILLFOCUS(IDC_AMPLITUDE, &AddHarmonicView::OnKillfocusAmplitude)
//	ON_EN_KILLFOCUS(IDC_FREQUENCE, &AddHarmonicView::OnKillfocusFrequency)
//	ON_EN_KILLFOCUS(IDC_PHASE, &AddHarmonicView::OnKillfocusPhase)
//	ON_BN_CLICKED(IDC_RADIO_SIN, &AddHarmonicView::OnClickedRadioSin)
//	ON_BN_CLICKED(IDC_RADIO_COS, &AddHarmonicView::OnClickedRadioCos)
//	ON_BN_CLICKED(IDC_BUTTON_ADD, &AddHarmonicView::OnClickedAddHarmonic)
//	ON_BN_CLICKED(IDC_BUTTON_DELETE, &AddHarmonicView::OnClickedDeleteHarmonic)
//	ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &AddHarmonicView::OnSetFocusListBox)*/
//
//	//ON_COMMAND(IDD_DIALOG1, &AddHarmonicView::OnKillFocusAmplitude)
//	//ON_CBN_SELCHANGE(IDC_COMBO1, &AddHarmonicView::OnCbnSelchangeCombo1)
//	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &AddHarmonicView::OnTcnSelchangeTab1)
//	//ON_CBN_SELCHANGE(IDC_COMBO3, &AddHarmonicView::OnCbnSelchangeCombo3)
//	//ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &AddHarmonicView::OnLbnSelchangeHarmonicsListbox)
////END_MESSAGE_MAP()
//