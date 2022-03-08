// CustomStrobeInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "CustomStrobeInfoDlg.h"


// CCustomStrobeInfoDlg dialog

IMPLEMENT_DYNCREATE(CCustomStrobeInfoDlg, CDialog)

CCustomStrobeInfoDlg::CCustomStrobeInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomStrobeInfoDlg::IDD, pParent)
{
}

CCustomStrobeInfoDlg::~CCustomStrobeInfoDlg()
{
}

void CCustomStrobeInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STROBE, m_List_Strobe);
	DDX_Control(pDX, IDC_COMBO_STROBE, m_Combo_Strobe);
	DDX_Control(pDX, IDC_COMBO_POLARITY, m_Combo_Polarity);
	DDX_Control(pDX, IDC_COMBO_STROBE_MODE, m_Combo_StrobeMode);
}

BOOL CCustomStrobeInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	m_List_Strobe.SetExtendedStyle( m_List_Strobe.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	int ncol = 0;
	m_List_Strobe.InsertColumn(ncol++, ("Index"), 0, 50);
	m_List_Strobe.InsertColumn(ncol++, ("ID"), 0, 50);
	m_List_Strobe.InsertColumn(ncol++, ("On/Off"), 0, 100);
	m_List_Strobe.InsertColumn(ncol++, ("Polarity"), 0, 80);
	m_List_Strobe.InsertColumn(ncol++, ("Strobe Mode"), 0, 100);
	m_List_Strobe.InsertColumn(ncol++, ("Delay"), 0, 60);
	m_List_Strobe.InsertColumn(ncol++, ("Duration"), 0, 70);



	m_Combo_Polarity.ResetContent();
	m_Combo_Polarity.AddString(("High"));
	m_Combo_Polarity.AddString(("Low"));
	m_Combo_Polarity.SetCurSel(0);


	m_Combo_Strobe.ResetContent();
	m_Combo_Strobe.AddString(("Off"));
	m_Combo_Strobe.AddString(("On"));
	m_Combo_Strobe.SetCurSel(0);

	m_Combo_StrobeMode.ResetContent();
	m_Combo_StrobeMode.AddString(("TriggerOnly"));
	m_Combo_StrobeMode.AddString(("TriggerAndLiveMode"));
	m_Combo_StrobeMode.SetCurSel(0);


	m_vInfo.clear();
	long nCount = SPIDER_GetCustomStrobeCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_CUSTOM_STROBE_INFO stInfo = {0};
		long lret = SPIDER_GetCustomStrobeInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);
		CString sztext;


		sztext.Format(("%d"), i+1);
		m_List_Strobe.InsertItem(i, sztext);


		int ncol = 1;

		sztext = stInfo.strID;
		m_List_Strobe.SetItemText(i, ncol++, sztext);

		if(stInfo.nsOnOff == 1)
			sztext = "On";
		else if(stInfo.nsOnOff == 0)
			sztext = "Off";
		else
			sztext = "";
		m_List_Strobe.SetItemText(i, ncol++, sztext);

		if(stInfo.nsPolarity == 0)
			sztext = "High";
		else if(stInfo.nsPolarity == 1)
			sztext = "Low";
		else
			sztext = "";
		m_List_Strobe.SetItemText(i, ncol++, sztext);

		if(stInfo.nsStrobeMode == 0)
			sztext = "TriggerOnly";
		else if(stInfo.nsStrobeMode == 1)
			sztext = "TriggerAndLiveMode";
		else
			sztext = "";
		m_List_Strobe.SetItemText(i, ncol++, sztext);

		sztext.Format(("%d"), stInfo.nDelay);
		m_List_Strobe.SetItemText(i, ncol++, sztext);

		sztext.Format(("%d"), stInfo.nDuration);
		m_List_Strobe.SetItemText(i, ncol++, sztext);


	}

	m_List_Strobe.SetSelectionMark(0);
	m_List_Strobe.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	DisplayInfo();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CCustomStrobeInfoDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STROBE, &CCustomStrobeInfoDlg::OnNMClickListStrobe)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CCustomStrobeInfoDlg::OnBnClickedButtonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_STROBE_MODE, &CCustomStrobeInfoDlg::OnCbnSelchangeComboStrobeMode)
END_MESSAGE_MAP()


// CCustomStrobeInfoDlg message handlers

void CCustomStrobeInfoDlg::OnNMClickListStrobe(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfo();

	*pResult = 0;
}

void CCustomStrobeInfoDlg::DisplayInfo()
{
	int nSel = m_List_Strobe.GetSelectionMark();
	if(nSel != -1 && nSel < m_vInfo.size())
	{
		ST_SPIDER_CUSTOM_STROBE_INFO stInfo = m_vInfo.at(nSel);


		CString sztext;

		sztext = stInfo.strID;
		GetDlgItem(IDC_EDIT_ID)->SetWindowText(sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MIN), stInfo.nMinDelay, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MAX), stInfo.nMaxDelay, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DURATION), stInfo.nDuration, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DELAY), stInfo.nDelay, sztext);
		_VALID_WND_WITH_VAL(m_Combo_Polarity, stInfo.nsPolarity, NULL);
		_VALID_WND_WITH_VAL(m_Combo_StrobeMode, stInfo.nsStrobeMode, NULL);
		
		if(stInfo.nsOnOff == 0)	//off
		{
			m_Combo_Strobe.SetCurSel(0);
			m_Combo_Strobe.EnableWindow(true);
		}
		else if(stInfo.nsOnOff == 1)	//on
		{
			m_Combo_Strobe.SetCurSel(1);
			m_Combo_Strobe.EnableWindow(true);
		}
		else
		{
			m_Combo_Strobe.EnableWindow(false);
			
			GetDlgItem(IDC_EDIT_MIN)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_MAX)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_DURATION)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(false);
			m_Combo_Polarity.EnableWindow(false);
		}
	}
}

void CCustomStrobeInfoDlg::OnBnClickedButtonApply()
{
	int nModifyIndex = m_List_Strobe.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_CUSTOM_STROBE_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	if(stNew.nsOnOff != 0xFFFF && stNew.nsOnOff != 0xFFFFFFFF)
		stNew.nsOnOff = m_Combo_Strobe.GetCurSel();

	if(stNew.nsPolarity != 0xFFFF && stNew.nsPolarity != 0xFFFFFFFF)
		stNew.nsPolarity = m_Combo_Polarity.GetCurSel();

	if(stNew.nsStrobeMode != 0xFFFF && stNew.nsStrobeMode != 0xFFFFFFFF)
		stNew.nsStrobeMode = m_Combo_StrobeMode.GetCurSel();

	int nValue = 0;
	GetDlgItem(IDC_EDIT_MIN)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nMinDelay != 0xFFFF && stNew.nMinDelay != 0xFFFFFFFF)
		stNew.nMinDelay = nValue;

	GetDlgItem(IDC_EDIT_MAX)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nMaxDelay != 0xFFFF && stNew.nMaxDelay != 0xFFFFFFFF)
		stNew.nMaxDelay = nValue;

	GetDlgItem(IDC_EDIT_DURATION)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nDuration != 0xFFFF && stNew.nDuration != 0xFFFFFFFF)
		stNew.nDuration = nValue;

	GetDlgItem(IDC_EDIT_DELAY)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nDelay != 0xFFFF && stNew.nDelay != 0xFFFFFFFF)
		stNew.nDelay = nValue;


	long lret = SPIDER_SetCustomStrobeInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));


}

void CCustomStrobeInfoDlg::OnCbnSelchangeComboStrobeMode()
{
	// TODO: Add your control notification handler code here
	int nSel = m_Combo_StrobeMode.GetCurSel();

	CString sztext;

	POSITION pos = m_List_Strobe.GetFirstSelectedItemPosition();
	while(pos)
	{
		int nItem = m_List_Strobe.GetNextSelectedItem(pos);
		if(nItem == -1)
			break;

		m_vInfo.at(nItem).nsStrobeMode = nSel;

		if(m_vInfo.at(nItem).nsStrobeMode == 0)
			sztext = "TriggerOnly";
		else if(m_vInfo.at(nItem).nsStrobeMode == 1)
			sztext = "TriggerAndLiveMode";
		else
			sztext = "";

		m_List_Strobe.SetItemText(nItem, 4, sztext);

		DisplayInfo();

	}
}
