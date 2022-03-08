// FeatureInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "FeatureInfoDlg.h"


// CFeatureInfoDlg dialog

IMPLEMENT_DYNCREATE(CFeatureInfoDlg, CDialog)

CFeatureInfoDlg::CFeatureInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFeatureInfoDlg::IDD, pParent)
{

}

CFeatureInfoDlg::~CFeatureInfoDlg()
{
}

void CFeatureInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_POWER_FREQUENCY, m_Combo_PowerFrequency);
	DDX_Control(pDX, IDC_COMBO_WB_MODE, m_Combo_WBMode);
	DDX_Control(pDX, IDC_COMBO_EXPOSURE_MODE, m_Combo_ExposureMode);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHT_TYPE, m_Combo_DayNightType);
	DDX_Control(pDX, IDC_CHECK_DAYNIGHT_SCHEDULE, m_Check_DayNightSchedule);
	DDX_Control(pDX, IDC_SLIDER_GAMMA, m_Slider_Gamma);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_Slider_Hue);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_Slider_Saturation);
	DDX_Control(pDX, IDC_SLIDER_SHARPNESS, m_Slider_Sharpness);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_Slider_Contrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_Slider_Brightness);
	DDX_Control(pDX, IDC_SLIDER_GAIN, m_Slider_Gain);
}

BOOL CFeatureInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Combo_PowerFrequency.ResetContent();
	m_Combo_PowerFrequency.AddString(("50"));
	m_Combo_PowerFrequency.AddString(("60"));
	m_Combo_PowerFrequency.SetCurSel(0);

	m_Combo_WBMode.ResetContent();
	m_Combo_WBMode.AddString(("manual"));
	m_Combo_WBMode.AddString(("auto"));
	m_Combo_WBMode.AddString(("indoor"));
	m_Combo_WBMode.AddString(("outdoor"));
	//m_Combo_WBMode.AddString(("fluorescent/white"));
	//m_Combo_WBMode.AddString(("fluorescent/yellow"));
	//m_Combo_WBMode.AddString(("black&white"));
	m_Combo_WBMode.SetCurSel(0);



	m_Combo_ExposureMode.ResetContent();	
	m_Combo_ExposureMode.AddString(("manual"));
	m_Combo_ExposureMode.AddString(("auto"));
	m_Combo_ExposureMode.SetCurSel(0);



	m_Combo_DayNightType.ResetContent();
	m_Combo_DayNightType.AddString(("day"));
	m_Combo_DayNightType.AddString(("night"));
	m_Combo_DayNightType.AddString(("auto"));
	m_Combo_DayNightType.SetCurSel(0);

	

	m_Check_DayNightSchedule.SetCheck(false);	

	m_Slider_Gamma.SetRange(0, 100);
	m_Slider_Gamma.SetPos(0);
	m_Slider_Hue.SetRange(0, 100);
	m_Slider_Hue.SetPos(0);
	m_Slider_Saturation.SetRange(0, 100);
	m_Slider_Saturation.SetPos(0);
	m_Slider_Sharpness.SetRange(0, 100);
	m_Slider_Sharpness.SetPos(0);
	m_Slider_Contrast.SetRange(0, 100);
	m_Slider_Contrast.SetPos(0);
	m_Slider_Brightness.SetRange(0, 100);
	m_Slider_Brightness.SetPos(0);
	m_Slider_Gain.SetRange(0, 100);
	m_Slider_Gain.SetPos(0);


	GetDlgItem(IDC_CHECK_GAMMA)->SendMessage(BM_SETCHECK);

	long lret = SPIDER_GetFeatureInfo(theApp.m_hSelectCamera, &m_stInfo);
	if(lret != E_CTRL_OK)
	{
		MessageBox(GetErrorString(lret), ("Fail"));
	}
	else
	{
		_DisplayInfo();
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CFeatureInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CFeatureInfoDlg::OnBnClickedButtonApply)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_GAMMA, &CFeatureInfoDlg::OnBnClickedCheckGamma)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPOSURE_MODE, &CFeatureInfoDlg::OnCbnSelchangeComboExposureMode)
END_MESSAGE_MAP()

// CFeatureInfoDlg message handlers



void CFeatureInfoDlg::OnBnClickedButtonApply()
{
	ST_SPIDER_FEATURE_INFO stNew = m_stInfo;

	CString sztext;

	GetDlgItem(IDC_EDIT_INPUT_PORT)->GetWindowText(sztext);
	if(strcmp(stNew.strPort, "NA"))
		StringCopyTo(sztext, stNew.strPort);


	if(GetDlgItem(IDC_CHECK_GAMMA)->SendMessage(BM_GETCHECK) == BST_CHECKED)
	{
		stNew.nsGammaEnable = 1;
	}
	else
	{
		stNew.nsGammaEnable = 0;
	}


	int nValue = 0;
	GetDlgItem(IDC_EDIT_GAMMA)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsGammaLevel != 0xFFFF && stNew.nsGammaLevel != 0xFFFFFFFF)
		stNew.nsGammaLevel = nValue;

	GetDlgItem(IDC_EDIT_HUE)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsHueLevel != 0xFFFF && stNew.nsHueLevel != 0xFFFFFFFF)
		stNew.nsHueLevel = nValue;

	GetDlgItem(IDC_EDIT_SATURATION)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsSaturationLevel != 0xFFFF && stNew.nsSaturationLevel != 0xFFFFFFFF)
		stNew.nsSaturationLevel = nValue;

	GetDlgItem(IDC_EDIT_SHARPNESS)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsSharpLevel != 0xFFFF && stNew.nsSharpLevel != 0xFFFFFFFF)
		stNew.nsSharpLevel = nValue;

	GetDlgItem(IDC_EDIT_GAIN)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsGainLevel != 0xFFFF && stNew.nsGainLevel != 0xFFFFFFFF)
		stNew.nsGainLevel = nValue;

	GetDlgItem(IDC_EDIT_BRIGHTNESS)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsBrightLevel != 0xFFFF && stNew.nsBrightLevel != 0xFFFFFFFF)
		stNew.nsBrightLevel = nValue;

	GetDlgItem(IDC_EDIT_CONTRAST)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsContrastLevel != 0xFFFF && stNew.nsContrastLevel != 0xFFFFFFFF)
		stNew.nsContrastLevel = nValue;

	GetDlgItem(IDC_EDIT_WB_LEVEL)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nsWBLevel != 0xFFFF && stNew.nsWBLevel != 0xFFFFFFFF)
		stNew.nsWBLevel = nValue;




	if(stNew.power_line_frequency_mode != 0xFFFF && stNew.power_line_frequency_mode != 0xFFFFFFFF)
		stNew.power_line_frequency_mode = m_Combo_PowerFrequency.GetCurSel();

	if(stNew.white_balance_mode != 0xFFFF && stNew.white_balance_mode != 0xFFFFFFFF)
		stNew.white_balance_mode = (ENUM_WB_MODE)m_Combo_WBMode.GetCurSel();




	//exposure
	if(stNew.nsExpMode != 0xFFFF && stNew.nsExpMode != 0xFFFFFFFF)
		stNew.nsExpMode = m_Combo_ExposureMode.GetCurSel();

	GetDlgItem(IDC_EDIT_EXPOSURE_TARGET)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nExpTarget != 0xFFFF && stNew.nExpTarget != 0xFFFFFFFF)
		stNew.nExpTarget = nValue;

	GetDlgItem(IDC_EDIT_EXPOSURE_MIN)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nExpAutoMin != 0xFFFF && stNew.nExpAutoMin != 0xFFFFFFFF)
		stNew.nExpAutoMin = nValue;

	GetDlgItem(IDC_EDIT_EXPOSURE_MAX)->GetWindowText(sztext);
	nValue = _ttoi(sztext);
	if(stNew.nExpAutoMax != 0xFFFF && stNew.nExpAutoMax != 0xFFFFFFFF)
		stNew.nExpAutoMax = nValue;


	


	//day night filter 
	if(stNew.nsDayNightMode != 0xFFFF && stNew.nsDayNightMode != 0xFFFFFFFF)
		stNew.nsDayNightMode = m_Combo_DayNightType.GetCurSel();

	GetDlgItem(IDC_EDIT_BEGIN_HOUR)->GetWindowText(sztext);
	if(strcmp(stNew.strPort, "NA"))
		StringCopyTo(sztext, stNew.strBeginTime);

	GetDlgItem(IDC_EDIT_END_HOUR)->GetWindowText(sztext);
	if(strcmp(stNew.strPort, "NA"))
		StringCopyTo(sztext, stNew.strEndTime);

	if(stNew.nsDayNightScheduleEnable != 0xFFFF && stNew.nsDayNightScheduleEnable != 0xFFFFFFFF)
		stNew.nsDayNightScheduleEnable = m_Check_DayNightSchedule.GetCheck();
	


	long lret = SPIDER_SetFeatureInfo(theApp.m_hSelectCamera, stNew);
	if(lret != E_CTRL_OK)
		MessageBox(GetErrorString(lret), ("Fail"));
	else
		MessageBox(("Success."));
}

void CFeatureInfoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CString text;

	CWnd* pbar = pScrollBar;
	if(pbar == &m_Slider_Gamma)
	{
		m_stInfo.nsGammaLevel = m_Slider_Gamma.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_GAMMA), m_stInfo.nsGammaLevel, text);
	}
	else if(pbar == &m_Slider_Hue)
	{
		m_stInfo.nsHueLevel = m_Slider_Hue.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_HUE), m_stInfo.nsHueLevel, text);
	}
	else if(pbar == &m_Slider_Saturation)
	{
		m_stInfo.nsSaturationLevel = m_Slider_Saturation.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SATURATION), m_stInfo.nsSaturationLevel, text);
	}
	else if(pbar == &m_Slider_Sharpness)
	{
		m_stInfo.nsSharpLevel = m_Slider_Sharpness.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SHARPNESS), m_stInfo.nsSharpLevel, text);
	}
	else if(pbar == &m_Slider_Contrast)
	{
		m_stInfo.nsContrastLevel = m_Slider_Contrast.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_CONTRAST), m_stInfo.nsContrastLevel, text);
	}
	else if(pbar == &m_Slider_Brightness)
	{
		m_stInfo.nsBrightLevel = m_Slider_Brightness.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BRIGHTNESS), m_stInfo.nsBrightLevel, text);
	}
	else if(pbar == &m_Slider_Gain)
	{
		m_stInfo.nsGainLevel = m_Slider_Gain.GetPos();
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_GAIN), m_stInfo.nsGainLevel, text);
	}
	

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFeatureInfoDlg::OnBnClickedCheckGamma()
{
		if(GetDlgItem(IDC_CHECK_GAMMA)->SendMessage(BM_GETCHECK) == BST_CHECKED)
		{
			m_Slider_Gamma.EnableWindow(true);
		}
		else
		{
			m_Slider_Gamma.EnableWindow(false);
		}
}

void CFeatureInfoDlg::OnCbnSelchangeComboExposureMode()
{
	m_stInfo.nsExpMode = m_Combo_ExposureMode.GetCurSel();
	_DisplayInfo();
}

void CFeatureInfoDlg::_DisplayInfo()
{
	CString sztext;

	ST_SPIDER_FEATURE_INFO stInfo = m_stInfo;

	sztext = stInfo.strID;
	GetDlgItem(IDC_EDIT_ID)->SetWindowText(sztext);

	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_INPUT_PORT), stInfo.strPort, sztext);




	//color
	if(stInfo.nsGainLevel >= 0xFFFF)
	{
		m_Slider_Gain.SetPos(0);
		m_Slider_Gain.EnableWindow(false);
	}
	else
	{
		m_Slider_Gain.SetPos(stInfo.nsGainLevel);
		m_Slider_Gain.EnableWindow(true);
	}

	if(stInfo.nsBrightLevel >= 0xFFFF)
	{
		m_Slider_Brightness.SetPos(0);
		m_Slider_Brightness.EnableWindow(false);
	}
	else
	{
		m_Slider_Brightness.SetPos(stInfo.nsBrightLevel);
		m_Slider_Brightness.EnableWindow(true);
	}

	if(stInfo.nsContrastLevel >= 0xFFFF)
	{
		m_Slider_Contrast.SetPos(0);
		m_Slider_Contrast.EnableWindow(false);
	}
	else
	{
		m_Slider_Contrast.SetPos(stInfo.nsContrastLevel);
		m_Slider_Contrast.EnableWindow(true);
	}

	if(stInfo.nsSharpLevel >= 0xFFFF)
	{
		m_Slider_Sharpness.SetPos(0);
		m_Slider_Sharpness.EnableWindow(false);
	}
	else
	{
		m_Slider_Sharpness.SetPos(stInfo.nsSharpLevel);
		m_Slider_Sharpness.EnableWindow(true);
	}

	if(stInfo.nsSaturationLevel >= 0xFFFF)
	{
		m_Slider_Saturation.SetPos(0);
		m_Slider_Saturation.EnableWindow(false);
	}
	else
	{
		m_Slider_Saturation.SetPos(stInfo.nsSaturationLevel);
		m_Slider_Saturation.EnableWindow(true);
	}

	if(stInfo.nsHueLevel >= 0xFFFF)
	{
		m_Slider_Hue.SetPos(0);
		m_Slider_Hue.EnableWindow(false);
	}
	else
	{
		m_Slider_Hue.SetPos(stInfo.nsHueLevel);
		m_Slider_Hue.EnableWindow(true);
	}

	if(stInfo.nsGammaLevel >= 0xFFFF)
	{
		m_Slider_Gamma.SetPos(0);
		m_Slider_Gamma.EnableWindow(false);
	}
	else
	{
		m_Slider_Gamma.SetPos(stInfo.nsGammaLevel);
		m_Slider_Gamma.EnableWindow(true);
	}

	if(stInfo.nsGammaEnable == 1)
	{
		GetDlgItem(IDC_CHECK_GAMMA)->SendMessage(BM_SETCHECK, BST_CHECKED);
		m_Slider_Gamma.EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_CHECK_GAMMA)->SendMessage(BM_SETCHECK);
		m_Slider_Gamma.EnableWindow(false);
	}

	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_GAMMA), stInfo.nsGammaLevel, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_HUE), stInfo.nsHueLevel, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SATURATION), stInfo.nsSaturationLevel, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_SHARPNESS), stInfo.nsSharpLevel, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_GAIN), stInfo.nsGainLevel, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BRIGHTNESS), stInfo.nsBrightLevel, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_CONTRAST), stInfo.nsContrastLevel, sztext);

	_VALID_WND_WITH_VAL(m_Combo_PowerFrequency, stInfo.power_line_frequency_mode, NULL);

	//white balance
		//case ENUM_SV_WB_MODE_MANUAL:
		//case ENUM_SV_WB_MODE_AUTO:
		//case ENUM_SV_WB_MODE_INDOOR:
		//case ENUM_SV_WB_MODE_OUTDOOR:
	_VALID_WND_WITH_VAL(m_Combo_WBMode, stInfo.white_balance_mode, NULL);


	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_WB_LEVEL), stInfo.nsWBLevel, sztext);



	//exposure
	_VALID_WND_WITH_VAL(m_Combo_ExposureMode, stInfo.nsExpMode, NULL);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_EXPOSURE_TARGET), stInfo.nExpTarget, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_EXPOSURE_MIN), stInfo.nExpAutoMin, sztext);
	_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_EXPOSURE_MAX), stInfo.nExpAutoMax, sztext);
	if(stInfo.nsExpMode == 0)	//manual
	{
		if(stInfo.nExpTarget != 0xFFFF && stInfo.nExpTarget != 0xFFFFFFFF)
			GetDlgItem(IDC_EDIT_EXPOSURE_TARGET)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_EXPOSURE_MIN)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_EXPOSURE_MAX)->EnableWindow(false);
	}
	else if(stInfo.nsExpMode == 1)	//auto
	{
		GetDlgItem(IDC_EDIT_EXPOSURE_TARGET)->EnableWindow(false);

		if(stInfo.nExpAutoMin != 0xFFFF && stInfo.nExpAutoMin != 0xFFFFFFFF)
			GetDlgItem(IDC_EDIT_EXPOSURE_MIN)->EnableWindow(true);
		if(stInfo.nExpAutoMax != 0xFFFF && stInfo.nExpAutoMax != 0xFFFFFFFF)
			GetDlgItem(IDC_EDIT_EXPOSURE_MAX)->EnableWindow(true);

		m_Slider_Gain.EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_EDIT_EXPOSURE_TARGET)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_EXPOSURE_MIN)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_EXPOSURE_MAX)->EnableWindow(false);
	}

	//day night filter 
	_VALID_WND_WITH_VAL(m_Combo_DayNightType, stInfo.nsDayNightMode, NULL);

	if(stInfo.nsDayNightMode >= 0xFFFF)
	{
		m_Check_DayNightSchedule.EnableWindow(false);
		m_Check_DayNightSchedule.SetCheck(false);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BEGIN_HOUR), 0xFFFF, sztext);
		_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_HOUR), 0xFFFF, sztext);

	}
	else
	{

		if(stInfo.nsDayNightScheduleEnable >= 0xFFFF)
		{
			m_Check_DayNightSchedule.EnableWindow(false);
			m_Check_DayNightSchedule.SetCheck(false);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BEGIN_HOUR), 0xFFFF, sztext);
			_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_HOUR), 0xFFFF, sztext);
		}
		else
		{
			m_Check_DayNightSchedule.EnableWindow(true);
			m_Check_DayNightSchedule.SetCheck(stInfo.nsDayNightScheduleEnable);

			if(stInfo.nsDayNightScheduleEnable == 1)
			{
				_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BEGIN_HOUR), stInfo.strBeginTime, sztext);
				_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_HOUR), stInfo.strEndTime, sztext);
			}
			else
			{
				_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_BEGIN_HOUR), 0xFFFF, sztext);
				_VALID_WND_WITH_VAL(GetDlgItem(IDC_EDIT_END_HOUR), 0xFFFF, sztext);
			}
		}
	}
}