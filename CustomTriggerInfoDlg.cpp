// CustomTriggerInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "CustomTriggerInfoDlg.h"


// CCustomTriggerInfoDlg dialog

IMPLEMENT_DYNCREATE(CCustomTriggerInfoDlg, CDialog)

CCustomTriggerInfoDlg::CCustomTriggerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomTriggerInfoDlg::IDD, pParent)
{

}

CCustomTriggerInfoDlg::~CCustomTriggerInfoDlg()
{
}

void CCustomTriggerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PARAM, m_List_Param);
	DDX_Control(pDX, IDC_COMBO_SOURCE, m_Combo_Source);
	DDX_Control(pDX, IDC_COMBO_POLARITY, m_Combo_Polarity);
	DDX_Control(pDX, IDC_COMBO_ONOFF, m_Combo_TriggerServerOnOff);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_FILE_SAVING, m_Combo_CaptureFileSaving);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_FORMAT, m_Combo_TriggerImage);
	DDX_Control(pDX, IDC_COMBO_TABLE_ONOFF, m_Combo_TableOnOff);
}

BOOL CCustomTriggerInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_List_Param.SetExtendedStyle( m_List_Param.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	m_List_Param.InsertColumn(0, ("Index"), 0, 50);
	m_List_Param.InsertColumn(1, ("ID"), 0, 40);
	m_List_Param.InsertColumn(2, ("Gain"), 0, 50);
	m_List_Param.InsertColumn(3, ("Shutter"), 0, 60);
	m_List_Param.InsertColumn(4, ("Increment"), 0, 70);



	m_Combo_Polarity.ResetContent();
	m_Combo_Polarity.AddString(("high"));
	m_Combo_Polarity.AddString(("low"));
	m_Combo_Polarity.SetCurSel(0);



	m_Combo_Source.ResetContent();
	m_Combo_Source.AddString(("software"));
	m_Combo_Source.AddString(("hardware"));
	m_Combo_Source.AddString(("periodic"));
	m_Combo_Source.AddString(("filterCtrl"));
	m_Combo_Source.SetCurSel(0);


	m_Combo_TriggerServerOnOff.ResetContent();
	m_Combo_TriggerServerOnOff.AddString(("Off"));
	m_Combo_TriggerServerOnOff.AddString(("On"));
	m_Combo_TriggerServerOnOff.SetCurSel(0);

	
	m_Combo_TableOnOff.ResetContent();
	m_Combo_TableOnOff.AddString(("Off"));
	m_Combo_TableOnOff.AddString(("On"));
	m_Combo_TableOnOff.SetCurSel(0);


	m_Combo_CaptureFileSaving.ResetContent();
	m_Combo_CaptureFileSaving.AddString(("network"));
	m_Combo_CaptureFileSaving.AddString(("SD Storage with Cyclic"));
	m_Combo_CaptureFileSaving.AddString(("SD Storage without Cyclic"));
	m_Combo_CaptureFileSaving.SetCurSel(0);

	m_Combo_TriggerImage.ResetContent();
	m_Combo_TriggerImage.AddString(("yuv"));
	m_Combo_TriggerImage.AddString(("jpg"));
	m_Combo_TriggerImage.SetCurSel(0);





	InitInfo();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CCustomTriggerInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_TRIGGER, &CCustomTriggerInfoDlg::OnBnClickedButtonModifyTrigger)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PARAM, &CCustomTriggerInfoDlg::OnNMClickListParam)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_PARAM, &CCustomTriggerInfoDlg::OnBnClickedButtonModifyParam)
	ON_BN_CLICKED(IDC_BUTTON_SET_TRIGGER, &CCustomTriggerInfoDlg::OnBnClickedButtonSetTrigger)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCustomTriggerInfoDlg::OnBnClickedButtonAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_POLARITY, &CCustomTriggerInfoDlg::OnCbnSelchangeComboPolarity)
	ON_CBN_SELCHANGE(IDC_COMBO_SOURCE, &CCustomTriggerInfoDlg::OnCbnSelchangeComboSource)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTURE_FORMAT, &CCustomTriggerInfoDlg::OnCbnSelchangeComboCaptureFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_CAPTURE_FILE_SAVING, &CCustomTriggerInfoDlg::OnCbnSelchangeComboCaptureFileSaving)
	ON_CBN_SELCHANGE(IDC_COMBO_TABLE_ONOFF, &CCustomTriggerInfoDlg::OnCbnSelchangeComboTableOnoff)
END_MESSAGE_MAP()


// CCustomTriggerInfoDlg message handlers

void CCustomTriggerInfoDlg::OnNMClickListParam(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: Add your control notification handler code here

	DisplayInfoParam();

	*pResult = 0;
}

void CCustomTriggerInfoDlg::DisplayInfoParam()
{
	int nSel = m_List_Param.GetSelectionMark();
	if(nSel != -1 && nSel < m_vInfo.size())
	{
		ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO stParam = m_vInfo.at(nSel);

		CString sztext;
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PARAM_ID), stParam.strID, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PARAM_GAIN), stParam.nGain, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PARAM_SHUTTER), stParam.nShutter, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PARAM_INCREMENT), stParam.nsIncrement, sztext);
	}
}

void CCustomTriggerInfoDlg::InitInfo()
{

	m_vInfo.clear();
	m_List_Param.DeleteAllItems();


	long lret = SPIDER_GetCustomTriggerInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail SPIDER_GetCustomTriggerInfo"));
	}
	else
	{
		DisplayInfoTrigger();
	}
}

void CCustomTriggerInfoDlg::OnBnClickedButtonSetTrigger()
{
	long lret = SPIDER_SetCustomTriggerSoftwareEvent(theApp.m_hSelectCamera);	
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}

void CCustomTriggerInfoDlg::OnBnClickedButtonModifyTrigger()
{
	ST_SPIDER_CUSTOM_TRIGGER_INFO stNew = m_stInfo;

	CString sztext;

	GetDlgItem(IDC_IPADDRESS1)->GetWindowText(sztext);
	if(strcmp(stNew.strIpAddr, "NA"))
		StringCopyTo(sztext, stNew.strIpAddr);

	if(stNew.nsOnOff != 0xFFFF && stNew.nsOnOff != 0xFFFFFFFF)
		stNew.nsOnOff = m_Combo_TriggerServerOnOff.GetCurSel();

	int nValue = 0;
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsPortNo != 0xFFFF && stNew.nsPortNo != 0xFFFFFFFF)
		stNew.nsPortNo = nValue;

	GetDlgItem(IDC_EDIT_PARAM)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsParameter != 0xFFFF && stNew.nsParameter != 0xFFFFFFFF)
		stNew.nsParameter = nValue;

	GetDlgItem(IDC_EDIT_DELAY)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nDelay != 0xFFFF && stNew.nDelay != 0xFFFFFFFF)
		stNew.nDelay = nValue;

	GetDlgItem(IDC_EDIT_NOISE_FILTER)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsTriggerNoiseFilter != 0xFFFF && stNew.nsTriggerNoiseFilter != 0xFFFFFFFF)
		stNew.nsTriggerNoiseFilter = nValue;

	GetDlgItem(IDC_EDIT_PERIODIC_INTERVAL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsPeriodicIntv != 0xFFFF && stNew.nsPeriodicIntv != 0xFFFFFFFF)
		stNew.nsPeriodicIntv = nValue;

	if(stNew.nsPolarity != 0xFFFF && stNew.nsPolarity != 0xFFFFFFFF)
		stNew.nsPolarity = m_Combo_Polarity.GetCurSel();

	if(stNew.nsSource != 0xFFFF && stNew.nsSource != 0xFFFFFFFF)
		stNew.nsSource = m_Combo_Source.GetCurSel();



	long lret = SPIDER_SetCustomTriggerInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void CCustomTriggerInfoDlg::OnBnClickedButtonModifyParam()
{
	int nModifyIndex = m_List_Param.GetSelectionMark();
	if(nModifyIndex >= m_vInfo.size())
		return;

	ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO stNew = m_vInfo.at(nModifyIndex);

	CString sztext;

	int nValue = 0;
	GetDlgItem(IDC_EDIT_PARAM_GAIN)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nGain != 0xFFFFFFFF)
		stNew.nGain = nValue;

	GetDlgItem(IDC_EDIT_PARAM_SHUTTER)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nShutter != 0xFFFFFFFF)
		stNew.nShutter = nValue;

	GetDlgItem(IDC_EDIT_PARAM_INCREMENT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsIncrement != 0xFFFF && stNew.nsIncrement != 0xFFFFFFFF)
		stNew.nsIncrement = nValue;

	long lret = SPIDER_SetCustomTriggerParamInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void CCustomTriggerInfoDlg::OnBnClickedButtonAdd()
{

	ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO stNew = {0};

	if(m_vInfo.size())
		stNew = m_vInfo.at(0);

	//make new id
	bool bNext = true;
	int nID = 0;
	while(bNext == true)
	{
		sprintf(stNew.strID, "%d", nID);

		bNext = false;
		int nIndex = 0;
		while(nIndex < m_vInfo.size())
		{
			if(strcmp(stNew.strID, m_vInfo.at(nIndex).strID) == 0)
			{
				bNext = true;
				break;
			}

			nIndex++;
		}

		nID++;
	}

	CString sztext;

	int nValue = 0;
	GetDlgItem(IDC_EDIT_PARAM_GAIN)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nGain != 0xFFFFFFFF)
		stNew.nGain = nValue;

	GetDlgItem(IDC_EDIT_PARAM_SHUTTER)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nShutter != 0xFFFFFFFF)
		stNew.nShutter = nValue;

	GetDlgItem(IDC_EDIT_PARAM_INCREMENT)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsIncrement != 0xFFFF && stNew.nsIncrement != 0xFFFFFFFF)
		stNew.nsIncrement = nValue;

	long lret = SPIDER_AddCustomTriggerParamInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));

	InitInfo();
}

void CCustomTriggerInfoDlg::OnCbnSelchangeComboPolarity()
{
	// TODO: Add your control notification handler code here
}

void CCustomTriggerInfoDlg::DisplayInfoTrigger()
{
	ST_SPIDER_CUSTOM_TRIGGER_INFO stTrigger = m_stInfo;
	CString sztext;
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PARAM), stTrigger.nsParameter, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_DELAY), stTrigger.nDelay, sztext);
	//_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_MODE), stTrigger.nsMode, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_NOISE_FILTER), stTrigger.nsTriggerNoiseFilter, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PERIODIC_INTERVAL), stTrigger.nsPeriodicIntv, sztext);

	_VALID_WND_WITH_VAL(m_Combo_TriggerImage, stTrigger.nsCaptureImageFormat, NULL);
	_VALID_WND_WITH_VAL(m_Combo_CaptureFileSaving, stTrigger.nsCaptureFileSaving, NULL);

	_VALID_WND_WITH_VAL(m_Combo_TableOnOff, stTrigger.nsGainShutterTableOnOff, NULL);
	
	

		//E_TRIGGER_POLARITY_HIGH = 0,	// "high"
		//E_TRIGGER_POLARITY_LOW		// "low"
	_VALID_WND_WITH_VAL(m_Combo_Polarity, stTrigger.nsPolarity, NULL);

		//E_TRIGGER_SOURCE_SOFTWARE = 0,	// "software"
		//E_TRIGGER_SOURCE_HARDWARE,			// "hardware"
		//E_TRIGGER_SOURCE_PERIODIC,		// "periodic"
		//E_TRIGGER_SOURCE_FILTERCTRL,		// "filterCtrl"
	_VALID_WND_WITH_VAL(m_Combo_Source, stTrigger.nsSource, NULL);	

	GetDlgItem(IDC_BUTTON_SET_TRIGGER)->EnableWindow(true);


	if(stTrigger.nsOnOff == 1)	//on
	{
		m_Combo_TriggerServerOnOff.SetCurSel(1);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS1), stTrigger.strIpAddr, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PORT), stTrigger.nsPortNo, sztext);
	}
	else if(stTrigger.nsOnOff == 0)	//off
	{
		m_Combo_TriggerServerOnOff.SetCurSel(0);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_IPADDRESS1), stTrigger.strIpAddr, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_PORT), stTrigger.nsPortNo, sztext);
	}



	//E_TRIGGER_SOURCE_SOFTWARE = 0,	// "software"
	//E_TRIGGER_SOURCE_HARDWARE,			// "hardware"
	//E_TRIGGER_SOURCE_PERIODIC,		// "periodic"
	//E_TRIGGER_SOURCE_FILTERCTRL,		// "filterCtrl"

	switch(stTrigger.nsSource)
	{
	case 0:
		m_Combo_Polarity.EnableWindow(false);
		GetDlgItem(IDC_EDIT_NOISE_FILTER)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(false);
		break;
	case 1:
		GetDlgItem(IDC_BUTTON_SET_TRIGGER)->EnableWindow(false);
		break;
	case 2:
		m_Combo_TriggerImage.EnableWindow(false);
		m_Combo_Polarity.EnableWindow(false);
		GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_SET_TRIGGER)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_PARAM)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_NOISE_FILTER)->EnableWindow(false);
		break;
	case 3:
		m_Combo_TriggerImage.EnableWindow(false);
		m_Combo_CaptureFileSaving.EnableWindow(false);
		GetDlgItem(IDC_EDIT_DELAY)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_SET_TRIGGER)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_PERIODIC_INTERVAL)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_PARAM)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_NOISE_FILTER)->EnableWindow(false);
		m_Combo_TriggerServerOnOff.EnableWindow(false);
		GetDlgItem(IDC_IPADDRESS1)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(false);
		break;
	}


	m_List_Param.DeleteAllItems();
	long nCount = SPIDER_GetCustomTriggerParamCount(theApp.m_hSelectCamera);
	for(int i = 0; i < nCount; i++)
	{
		ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO stInfo = {0};
		long lret = SPIDER_GetCustomTriggerParamInfo(theApp.m_hSelectCamera, i, &stInfo);
		if(lret != E_CTRL_OK)
		{
			MessageBox(GetErrorString(lret), ("Fail"));
			break;
		}

		m_vInfo.push_back(stInfo);


		int nSubItem = 1;

		sztext.Format(("%d"), i+1);
		m_List_Param.InsertItem(i, sztext);

		sztext = stInfo.strID;
		m_List_Param.SetItemText(i, nSubItem++, sztext);	

		sztext.Format(("%d"), stInfo.nGain);
		m_List_Param.SetItemText(i, nSubItem++, sztext);	

		sztext.Format(("%d"), stInfo.nShutter);
		m_List_Param.SetItemText(i, nSubItem++, sztext);	

		sztext.Format(("%d"), stInfo.nsIncrement);
		m_List_Param.SetItemText(i, nSubItem++, sztext);
	}

	m_List_Param.SetSelectionMark(0);
	m_List_Param.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	DisplayInfoParam();
}

void CCustomTriggerInfoDlg::OnCbnSelchangeComboSource()
{
	// TODO: Add your control notification handler code here

	m_stInfo.nsSource = m_Combo_Source.GetCurSel();
	DisplayInfoTrigger();
}

void CCustomTriggerInfoDlg::OnCbnSelchangeComboCaptureFormat()
{
	m_stInfo.nsCaptureImageFormat = m_Combo_TriggerImage.GetCurSel();
	DisplayInfoTrigger();
}

void CCustomTriggerInfoDlg::OnCbnSelchangeComboCaptureFileSaving()
{
	m_stInfo.nsCaptureFileSaving = m_Combo_CaptureFileSaving.GetCurSel();
	DisplayInfoTrigger();
}

void CCustomTriggerInfoDlg::OnCbnSelchangeComboTableOnoff()
{
	m_stInfo.nsGainShutterTableOnOff = m_Combo_TableOnOff.GetCurSel();
	DisplayInfoTrigger();
	
}
