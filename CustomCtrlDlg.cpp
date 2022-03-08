// CustomCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CustomCtrlDlg.h"
#include "TestDlg.h"


// CCustomCtrlDlg dialog

IMPLEMENT_DYNAMIC(CCustomCtrlDlg, CDialog)

CCustomCtrlDlg::CCustomCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomCtrlDlg::IDD, pParent)
	, m_nChannelCnt(0)
	, m_nChannel(0)
{

}

CCustomCtrlDlg::~CCustomCtrlDlg()
{
}

void CCustomCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AUTOCLIP_MODE, m_Combo_AutoClipMode);
	DDX_Control(pDX, IDC_COMBO_ENABLE, m_Combo_Enable);
	DDX_Control(pDX, IDC_COMBO_MAX_VALUE, m_Combo_MaxValue);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_CNT, m_nChannelCnt);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cbChannel);
	DDX_CBIndex(pDX, IDC_COMBO_CHANNEL, m_nChannel);
	DDX_Control(pDX, IDC_BUTTON_CHANNEL_SYNC, m_btnChannelSync);
	DDX_Control(pDX, IDC_BUTTON_CHANNEL_MODIFY, m_btnChannelModify);
	DDX_Control(pDX, IDC_COMBO_VIDEO_OUT_ENABLE, m_cbVideoOutEnable);
	DDX_Control(pDX, IDC_COMBO_VIDEO_OUT_TYPE, m_cbVideoOutType);
	DDX_Control(pDX, IDC_COMBO_DEFOG_TYPE, m_cbDefog);
	DDX_Control(pDX, IDC_COMBO_AGC_TYPE, m_cbAgcType);
	DDX_Control(pDX, IDC_COMBO_RECORD_ENABLE, m_cbRecordEnable);
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_cbRecordType);
	DDX_Control(pDX, IDC_COMBO_STROBE_NIGHT_ENABLE, m_cbStrobeNightOnly);
	DDX_Control(pDX, IDC_COMBO_STROBE_STRENGTH, m_cbStrobeStrength);
}


BEGIN_MESSAGE_MAP(CCustomCtrlDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_AUTOCLIP_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonAutoclipModify)
	ON_BN_CLICKED(IDC_BUTTON_SENSOR_UP_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonSensorUpModify)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonChannelModify)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL_SYNC, &CCustomCtrlDlg::OnBnClickedButtonChannelSync)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_OUT_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonVideoOutModify)
	ON_BN_CLICKED(IDC_BUTTON_DEFOG_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonDefogModify)
	ON_BN_CLICKED(IDC_BUTTON_AGC_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonAgcModify)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonRecordModify)
	ON_BN_CLICKED(IDC_BUTTON_STROBE_NIGHT_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonStrobeNightModify)
	ON_BN_CLICKED(IDC_BUTTON_STROBE_STRENGTH_MODIFY, &CCustomCtrlDlg::OnBnClickedButtonStrobeStrengthModify)
END_MESSAGE_MAP()


// CCustomCtrlDlg message handlers

BOOL CCustomCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_Combo_AutoClipMode.AddString(("disable"));
	m_Combo_AutoClipMode.AddString(("enable"));
	m_Combo_AutoClipMode.SetCurSel(0);



	bool bEnable = false;
	long lret = 0;
	HCAMERA hCamera = theApp.m_hSelectCamera;


	//auto clip mode & night clip value
	{
		ST_SPIDER_CUSTOM_AUTOCLIP stAutoClip = {0};
		lret = SPIDER_GetCustomAutoClip(hCamera, &stAutoClip);
		if(lret != E_CTRL_OK)
		{
			m_Combo_AutoClipMode.EnableWindow(false);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->EnableWindow(false);
			m_Combo_AutoClipMode.SetCurSel(0);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->SetWindowText((""));
		}
		else
		{
			if(stAutoClip.bEnabled > 1)
				m_Combo_AutoClipMode.EnableWindow(false);
			else
				m_Combo_AutoClipMode.EnableWindow(true);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->EnableWindow(true);

			m_Combo_AutoClipMode.SetCurSel(stAutoClip.bEnabled?1:0);			
			SetDlgItemInt(IDC_EDIT_NIGHTCLIP_VALUE, stAutoClip.nNightClipValue);
		}
	}


	m_Combo_Enable.ResetContent();
	m_Combo_Enable.AddString("Disable");
	m_Combo_Enable.AddString("Enable");
	m_Combo_Enable.SetCurSel(0);

	m_Combo_MaxValue.ResetContent();

	{
		bEnable = false;

		int ncount = 0;
		int MaxValueList[50] = {0};
		lret = SPIDER_GetSensorUpMaxList(hCamera, &ncount, MaxValueList);
		if(lret == E_CTRL_OK)
		{
			CString sztext;
			for(int i = 0; i < ncount; i++)
			{
				sztext.Format("%d", MaxValueList[i]);
				m_Combo_MaxValue.AddString(sztext);
			}

			int nMax = 0;
			lret = SPIDER_GetSensorUpInfo(hCamera, &bEnable, &nMax);
			if(lret == E_CTRL_OK)
			{
				m_Combo_Enable.SetCurSel(bEnable);
				sztext.Format("%d", nMax);
				m_Combo_MaxValue.SetWindowText(sztext);
				
				bEnable = true;
			}
		}
		m_Combo_Enable.EnableWindow(bEnable);
		m_Combo_MaxValue.EnableWindow(bEnable);	
		GetDlgItem(IDC_BUTTON_SENSOR_UP_MODIFY)->EnableWindow(bEnable);
	}




	//this is example.
#if 0
	//ENUM_SPIDER_CUSTOM_ASPECTRATIO eAspectRatio = E_ASPECT_RAIO_SQUEEZING;
	//lret = SPIDER_SetCustomAspectRatio(hCamera, eAspectRatio);


	//ENUM_SPIDER_CUSTOM_LINKSPEED eLinkSpeed = E_LINK_SPEED_AUTO;
	//lret = SPIDER_SetCustomLinkSpeed(hCamera, eLinkSpeed);

	
	//lret = SPIDER_SetCustomSuppressColorNightMode(hCamera, bEnable);


	ST_SPIDER_CUSTOM_AUTOCLIP stAutoClip = {0};
	lret = SPIDER_GetCustomAutoClip(hCamera, &stAutoClip);

	//stAutoClip.bEnabled = true;
	//stAutoClip.nNightClipValue = 20;
	stAutoClip.bEnabled = false;
	stAutoClip.nNightClipValue = 0;
	lret = SPIDER_SetCustomAutoClip(hCamera, stAutoClip);


	bEnable = false;
	lret = SPIDER_GetCustomDeimpulse(hCamera, &bEnable);

	ST_SPIDER_CUSTOM_DENOISE stDenoise;
	lret = SPIDER_GetCustomDenoise(hCamera, &stDenoise);


	ST_SPIDER_CUSTOM_JPG_QUALITY stQuality;
	lret = SPIDER_GetCustomJPGQuality(hCamera, &stQuality);

	ST_SPIDER_CUSTOM_PRODUCT_TYPE stType;
	lret = SPIDER_GetCustomProductType(hCamera, &stType);

	ST_SPIDER_CUSTOM_AUTO_EXPOSURE_AREA stArea;
	lret = SPIDER_GetCustomAutoExposureArea(hCamera, &stArea);


	ST_SPIDER_CUSTOM_ISP stISP;
	lret = SPIDER_GetCustomISP(hCamera, &stISP);
#endif

	CreateChannelComboBox();
	QueryChannelCount();

	InitVideoOut();
	InitDefog();
	InitAgc();
	InitRecord();
	InitStrobeNightOnly();
	InitStrobeStrength();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomCtrlDlg::OnBnClickedButtonAutoclipModify()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_hSelectCamera == NULL)
	{
		MessageBox(("Select camera to be imported configuration."));
		return;
	}

	long lret = 0;
	HCAMERA hCamera = theApp.m_hSelectCamera;

	ST_SPIDER_CUSTOM_AUTOCLIP stAutoClip = {0};
	lret = SPIDER_GetCustomAutoClip(hCamera, &stAutoClip);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
		return;
	}

	stAutoClip.bEnabled = m_Combo_AutoClipMode.GetCurSel();

	CString sztext;
	GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->GetWindowText(sztext);	
	stAutoClip.nNightClipValue = atoi(sztext.GetBuffer());
	sztext.ReleaseBuffer();

	lret = SPIDER_SetCustomAutoClip(hCamera, stAutoClip);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		MessageBox(("Success."));

		lret = SPIDER_GetCustomAutoClip(hCamera, &stAutoClip);
		if(lret != E_CTRL_OK)
		{
			m_Combo_AutoClipMode.EnableWindow(false);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->EnableWindow(false);

			m_Combo_AutoClipMode.SetCurSel(0);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->SetWindowText((""));
		}
		else
		{
			if(stAutoClip.bEnabled > 1)
				m_Combo_AutoClipMode.EnableWindow(false);
			else
				m_Combo_AutoClipMode.EnableWindow(true);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->EnableWindow(true);

			m_Combo_AutoClipMode.SetCurSel(stAutoClip.bEnabled?1:0);
			sztext.Format(("%d"), stAutoClip.nNightClipValue);
			GetDlgItem(IDC_EDIT_NIGHTCLIP_VALUE)->SetWindowText(sztext);
		}
	}
}

void CCustomCtrlDlg::OnBnClickedButtonSensorUpModify()
{
	long lret = 0;
	HCAMERA hCamera = theApp.m_hSelectCamera;

	bool bEnable = m_Combo_Enable.GetCurSel();

	CString sztext;
	m_Combo_MaxValue.GetWindowText(sztext);

	int nMaxValue = atoi(sztext.GetBuffer());
	sztext.ReleaseBuffer();

	lret = SPIDER_SetSensorUpInfo(hCamera, bEnable, nMaxValue);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		MessageBox(("Success."));
	}
}


void CCustomCtrlDlg::OnBnClickedButtonChannelModify()
{
	int nItem = m_cbChannel.GetCurSel();
	if (nItem != CB_ERR) {
		ENUM_MULTI_CHANNEL_INDEX eIndex = (ENUM_MULTI_CHANNEL_INDEX)nItem;
		long ret = SPIDER_SetMultiChannelView(theApp.m_hSelectCamera, eIndex);
		if (ret == E_CTRL_OK) {
			MessageBox(("Success."));
		} else {
			MessageBox(("Failed channel modify."));
		}
	}
}


void CCustomCtrlDlg::OnBnClickedButtonChannelSync()
{
	long ret = SPIDER_SetMultiChannelSync(theApp.m_hSelectCamera);
	if (ret == E_CTRL_OK) {
		MessageBox(("Success."));
	} else {
		MessageBox(("Failed channel sync."));
	}

}

void CCustomCtrlDlg::CreateChannelComboBox()
{
	m_cbChannel.InsertString(0, _T("All"));
	m_cbChannel.InsertString(1, _T("Ch 1"));
	m_cbChannel.InsertString(2, _T("Ch 2"));
	m_cbChannel.InsertString(3, _T("Ch 3"));
	m_cbChannel.InsertString(4, _T("Ch 4"));

	m_cbChannel.SetCurSel(0);
}

void CCustomCtrlDlg::QueryChannelCount()
{
	m_nChannelCnt = 0;

	int nCount = 0;
	long ret = SPIDER_GetMultiChannelCount(theApp.m_hSelectCamera, &nCount);
	if (ret == E_CTRL_OK) {
		m_nChannelCnt = (UINT)nCount;
	}
	UpdateData(FALSE);

	m_cbChannel.EnableWindow(m_nChannelCnt > 1);
	m_btnChannelModify.EnableWindow(m_nChannelCnt > 1);
	m_btnChannelSync.EnableWindow(m_nChannelCnt > 1);
}

void CCustomCtrlDlg::InitVideoOut()
{
	m_cbVideoOutEnable.AddString(_T("disable"));
	m_cbVideoOutEnable.AddString(_T("enable"));

	m_cbVideoOutType.AddString(_T("NTSC"));
	m_cbVideoOutType.AddString(_T("PAL"));

	BOOL bEnabled = FALSE;
	VIDEO_OUTPUT_FORMAT VideoOutputFmt;
	long ret = SPIDER_GetVideoOutput(theApp.m_hSelectCamera, &bEnabled, &VideoOutputFmt);
	if (ret == E_CTRL_OK) {
		m_cbVideoOutEnable.SetCurSel(bEnabled ? 1:0);
		m_cbVideoOutType.SetCurSel(VideoOutputFmt == VIDEO_OUTPUT_FORMAT_NTSC ? 0:1);
	} else {
		m_cbVideoOutEnable.EnableWindow(FALSE);
		m_cbVideoOutType.EnableWindow(FALSE);
	}
}

void CCustomCtrlDlg::OnBnClickedButtonVideoOutModify()
{
	int nSelVideoOutEnable	= m_cbVideoOutEnable.GetCurSel();
	int nSelVideoOutType	= m_cbVideoOutType.GetCurSel();
	if (nSelVideoOutEnable != -1 && nSelVideoOutType != -1) {
		long nlRet = SPIDER_SetVideoOutput(theApp.m_hSelectCamera, 
										  (nSelVideoOutEnable == 1) ? TRUE:FALSE, 
										  (nSelVideoOutType == 0) ? VIDEO_OUTPUT_FORMAT_NTSC:VIDEO_OUTPUT_FORMAT_PAL);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
		}
	}
}

void CCustomCtrlDlg::InitDefog()
{
	m_cbDefog.AddString(_T("off"));
	m_cbDefog.AddString(_T("low"));
	m_cbDefog.AddString(_T("middle"));
	m_cbDefog.AddString(_T("high"));

	DEFOG_TYPE defogType;
	long ret = SPIDER_GetDefog(theApp.m_hSelectCamera, &defogType);
	if (ret == E_CTRL_OK) {
		int nSel = -1;
		switch (defogType) {
		case DEFOG_TYPE_OFF:	nSel = 0; break;
		case DEFOG_TYPE_LOW:	nSel = 1; break;
		case DEFOG_TYPE_MID:	nSel = 2; break;
		case DEFOG_TYPE_HIGH:	nSel = 3; break;
		}
		if (nSel != -1) {
			m_cbDefog.SetCurSel(nSel);
		}
	} else {
		m_cbDefog.EnableWindow(FALSE);
	}
}

void CCustomCtrlDlg::OnBnClickedButtonDefogModify()
{
	int nSelDefog = m_cbDefog.GetCurSel();
	if (nSelDefog != -1) {
		DEFOG_TYPE defogType;
		switch (nSelDefog) {
		case 0: defogType = DEFOG_TYPE_OFF;		break;
		case 1: defogType = DEFOG_TYPE_LOW;		break;
		case 2: defogType = DEFOG_TYPE_MID;		break;
		case 3: defogType = DEFOG_TYPE_HIGH;	break;
		}

		long nlRet = SPIDER_SetDefog(theApp.m_hSelectCamera, defogType);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
		}
	}
}

void CCustomCtrlDlg::InitAgc()
{
	m_cbAgcType.AddString(_T("off"));
	m_cbAgcType.AddString(_T("low"));
	m_cbAgcType.AddString(_T("middle"));
	m_cbAgcType.AddString(_T("high"));

	AUTO_GAIN_TYPE AgcType;
	long ret = SPIDER_GetAutoGainCtrl(theApp.m_hSelectCamera, &AgcType);
	if (ret == E_CTRL_OK) {
		int nSel = -1;
		switch (AgcType) {
		case AUTO_GAIN_TYPE_OFF:	nSel = 0; break;
		case AUTO_GAIN_TYPE_LOW:	nSel = 1; break;
		case AUTO_GAIN_TYPE_MID:	nSel = 2; break;
		case AUTO_GAIN_TYPE_HIGH:	nSel = 3; break;
		case AUTO_GAIN_TYPE_MANUAL:	nSel = 3; break;
		}
		if (nSel != -1) {
			m_cbAgcType.SetCurSel(nSel);
		}
	} else {
		m_cbAgcType.EnableWindow(FALSE);
	}
}

void CCustomCtrlDlg::OnBnClickedButtonAgcModify()
{
	int nSelAgc = m_cbDefog.GetCurSel();
	if (nSelAgc != -1) {
		AUTO_GAIN_TYPE AgcType;
		switch (nSelAgc) {
		case 0: AgcType = AUTO_GAIN_TYPE_OFF;		break;
		case 1: AgcType = AUTO_GAIN_TYPE_LOW;		break;
		case 2: AgcType = AUTO_GAIN_TYPE_MID;		break;
		case 3: AgcType = AUTO_GAIN_TYPE_HIGH;		break;
		case 4: AgcType = AUTO_GAIN_TYPE_MANUAL;	break;
		}

		long nlRet = SPIDER_SetAutoGainCtrl(theApp.m_hSelectCamera, AgcType);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
		}
	}
}

void CCustomCtrlDlg::InitRecord()
{
	m_cbRecordEnable.AddString(_T("disable"));
	m_cbRecordEnable.AddString(_T("enable"));

	m_cbRecordType.AddString(_T("video"));
	m_cbRecordType.AddString(_T("image"));

	BOOL bEnabled = FALSE;
	RECORD_TYPE RecordType;
	long ret = SPIDER_GetPrePostRecord(theApp.m_hSelectCamera, &bEnabled, &RecordType);
	if (ret == E_CTRL_OK) {
		m_cbRecordEnable.SetCurSel(bEnabled ? 1:0);
		m_cbRecordType.SetCurSel(RecordType == RECORD_TYPE_VIDEO ? 0:1);
	} else {
		m_cbRecordEnable.EnableWindow(FALSE);
		m_cbRecordType.EnableWindow(FALSE);
	}
}

void CCustomCtrlDlg::OnBnClickedButtonRecordModify()
{
	int nSelRecordEnable	= m_cbRecordEnable.GetCurSel();
	int nSelRecordType		= m_cbRecordType.GetCurSel();
	if (nSelRecordEnable != -1 && nSelRecordType != -1) {
		long nlRet = SPIDER_SetPrePostRecord(theApp.m_hSelectCamera, 
			(nSelRecordEnable == 1) ? TRUE:FALSE, 
			(nSelRecordType == 0) ? RECORD_TYPE_VIDEO:RECORD_TYPE_IMAGE);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
		}
	}
}

void CCustomCtrlDlg::InitStrobeNightOnly()
{
	m_cbStrobeNightOnly.AddString(_T("disable"));
	m_cbStrobeNightOnly.AddString(_T("enable"));

	BOOL bEnabled = FALSE;
	long ret = SPIDER_GetStrobeNightOnly(theApp.m_hSelectCamera, &bEnabled);
	if (ret == E_CTRL_OK) {
		m_cbStrobeNightOnly.SetCurSel(bEnabled ? 1:0);
	} else {
		m_cbStrobeNightOnly.EnableWindow(FALSE);
	}
}

void CCustomCtrlDlg::OnBnClickedButtonStrobeNightModify()
{
	int nSelStrobeNightOnlyEnable = m_cbStrobeNightOnly.GetCurSel();
	if (nSelStrobeNightOnlyEnable != -1) {
		long nlRet = SPIDER_SetStrobeNightOnly(theApp.m_hSelectCamera, (nSelStrobeNightOnlyEnable == 1) ? TRUE:FALSE);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
		}
	}
}

void CCustomCtrlDlg::InitStrobeStrength()
{
	m_cbStrobeStrength.AddString(_T("1"));
	m_cbStrobeStrength.AddString(_T("2"));
	m_cbStrobeStrength.AddString(_T("3"));
	m_cbStrobeStrength.AddString(_T("4"));

	LONG nlValue = 0;
	long ret = SPIDER_GetStrobeStrength(theApp.m_hSelectCamera, &nlValue);
	if (ret == E_CTRL_OK) {
		BOOL bFind = FALSE;
		for (int i=0; i<m_cbStrobeStrength.GetCount(); i++) {
			CString strText = _T("");
			m_cbStrobeStrength.GetLBText(i, strText);
			if (nlValue == _ttol(strText)) {
				m_cbStrobeStrength.SetCurSel(i);
				bFind = TRUE;
				break;
			}
		}
		if (!bFind) {
			m_cbStrobeStrength.EnableWindow(FALSE);
		}
	} else {
		m_cbStrobeStrength.EnableWindow(FALSE);
	}
}

void CCustomCtrlDlg::OnBnClickedButtonStrobeStrengthModify()
{
	int nSelStrobeStrength = m_cbStrobeStrength.GetCurSel();
	if (nSelStrobeStrength != -1) {
		CString strText = _T("");
		m_cbStrobeStrength.GetLBText(nSelStrobeStrength, strText);
		LONG nlValue = _ttol(strText);
		long nlRet = SPIDER_SetStrobeStrength(theApp.m_hSelectCamera, nlValue);
		if (nlRet != E_CTRL_OK) {
			MessageBox(GetErrorString(nlRet), _T("Fail"));
		} else {
			MessageBox(_T("Success."));
		}
	}
}
