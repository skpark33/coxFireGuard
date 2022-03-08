// ThermalCtrlInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TestDlg.h"
#include "ThermalCtrlInfoDlg.h"
#include "ThermalRegionInfoDlg.h"
#include "ThermalCorrectionInfoDlg.h"
#include "ThermalTempInfoDlg.h"

// CThermalCtrlInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CThermalCtrlInfoDlg, CDialog)

CThermalCtrlInfoDlg::CThermalCtrlInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThermalCtrlInfoDlg::IDD, pParent)
	, m_nlGainMin(0)
	, m_nlGainMax(0)
	, m_nlBrightness(0)
	, m_nlContrast(0)
	, m_bClrInvert(FALSE)
	, m_bGainAuto(FALSE)
	, m_bShowCenter(FALSE)
	, m_bShowIndicator(FALSE)
	, m_bShowTemperature(FALSE)
	, m_bShowClrBar(FALSE)
{
	ZeroMemory(&m_thermalComponents, sizeof(m_thermalComponents));
	m_thermalComponents.ulStructSize = sizeof(m_thermalComponents);

	ZeroMemory(&m_thermalCtrlValue, sizeof(m_thermalCtrlValue));
}

CThermalCtrlInfoDlg::~CThermalCtrlInfoDlg()
{
}

void CThermalCtrlInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_THERMAL_VER, m_edtThermalVer);
	DDX_Control(pDX, IDC_COMBO_PALETTE, m_cbPalette);
	DDX_Control(pDX, IDC_CHECK_CLR_INVERT, m_btnClrInvert);
	DDX_Control(pDX, IDC_RADIO_GAIN_MANUAL, m_btnGainManual);
	DDX_Control(pDX, IDC_RADIO_GAIN_AUTO, m_btnGainAuto);
	DDX_Control(pDX, IDC_EDIT_GAIN_MIN, m_edtGainMin);
	DDX_Control(pDX, IDC_EDIT_GAIN_MAX, m_edtGainMax);
	DDX_Control(pDX, IDC_EDIT_BRIGHTNESS, m_edtBrightness);
	DDX_Control(pDX, IDC_EDIT_CONTRAST, m_edtContrast);
	DDX_Control(pDX, IDC_COMBO_TEMP_MODE, m_cbTempMode);
	DDX_Control(pDX, IDC_COMBO_NRF, m_cbNRF);
	DDX_Control(pDX, IDC_COMBO_EDGE_ENHANCE, m_cbEdgeEnhance);
	DDX_Control(pDX, IDC_COMBO_NUC_TIME, m_cbNUCTime);
	DDX_Control(pDX, IDC_COMBO_NUC_AUTO, m_cbNUCAuto);
	DDX_Control(pDX, IDC_CHECK_SHOW_CENTER, m_btnShowCenter);
	DDX_Control(pDX, IDC_CHECK_SHOW_INDICATOR, m_btnShowIndicator);
	DDX_Control(pDX, IDC_CHECK_SHOW_TEMP, m_btnShowTemp);
	DDX_Control(pDX, IDC_CHECK_SHOW_CLR_BAR, m_btnShowClrBar);
	DDX_Text(pDX, IDC_EDIT_GAIN_MIN, m_nlGainMin);
	DDV_MinMaxLong(pDX, m_nlGainMin, 0, 16383);
	DDX_Text(pDX, IDC_EDIT_GAIN_MAX, m_nlGainMax);
	DDV_MinMaxLong(pDX, m_nlGainMax, 0, 16383);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_nlBrightness);
	DDV_MinMaxLong(pDX, m_nlBrightness, 0, 100);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_nlContrast);
	DDV_MinMaxLong(pDX, m_nlContrast, 0, 100);
	DDX_Check(pDX, IDC_CHECK_CLR_INVERT, m_bClrInvert);
	DDX_Radio(pDX, IDC_RADIO_GAIN_MANUAL, m_bGainAuto);
	DDX_Check(pDX, IDC_CHECK_SHOW_CENTER, m_bShowCenter);
	DDX_Check(pDX, IDC_CHECK_SHOW_INDICATOR, m_bShowIndicator);
	DDX_Check(pDX, IDC_CHECK_SHOW_TEMP, m_bShowTemperature);
	DDX_Check(pDX, IDC_CHECK_SHOW_CLR_BAR, m_bShowClrBar);
	DDX_Control(pDX, IDC_BUTTON_SET_REGION_ALARM, m_btnSetRegionAlarm);
	DDX_Control(pDX, IDC_BUTTON_THERMAL_CORRECTION, m_btnThermalCorrection);
}


BEGIN_MESSAGE_MAP(CThermalCtrlInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_THERMAL_MODIFY, &CThermalCtrlInfoDlg::OnBnClickedButtonThermalModify)
	ON_BN_CLICKED(IDC_RADIO_GAIN_MANUAL, &CThermalCtrlInfoDlg::OnBnClickedRadioGain)
	ON_BN_CLICKED(IDC_RADIO_GAIN_AUTO, &CThermalCtrlInfoDlg::OnBnClickedRadioGain)
	ON_BN_CLICKED(IDC_BUTTON_SET_REGION_ALARM, &CThermalCtrlInfoDlg::OnBnClickedButtonSetRegionAlarm)
	ON_BN_CLICKED(IDC_BUTTON_THERMAL_CORRECTION, &CThermalCtrlInfoDlg::OnBnClickedButtonThermalCorrection)
	ON_BN_CLICKED(IDC_BUTTON_GET_REGION_ALARM, &CThermalCtrlInfoDlg::OnBnClickedButtonGetRegionAlarm)
	ON_BN_CLICKED(IDC_BUTTON_SET_NUC, &CThermalCtrlInfoDlg::OnBnClickedButtonSetNuc)
END_MESSAGE_MAP()


// CThermalCtrlInfoDlg 메시지 처리기입니다.


BOOL CThermalCtrlInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCtrl();
	Initialize();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CThermalCtrlInfoDlg::CreateCtrl()
{
	int nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("Grey"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteGrey);
	}
	nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("Iron"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteIron);
	}
	nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("Rainbow"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteRainbow);
	}
	nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("GreyRed"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteGreyRed);
	}
	nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("Glowbow"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteGlowbow);
	}
	nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("Yellow"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteYellow);
	}
	nIndex = m_cbPalette.InsertString(m_cbPalette.GetCount(), _T("MidGrey"));
	if (nIndex != CB_ERR) {
		m_cbPalette.SetItemData(nIndex, PaletteMidGrey);
	}

	nIndex = m_cbTempMode.InsertString(m_cbTempMode.GetCount(), _T("Normal"));
	if (nIndex != CB_ERR) {
		m_cbTempMode.SetItemData(nIndex, TempModeNormal);
	}
	nIndex = m_cbTempMode.InsertString(m_cbTempMode.GetCount(), _T("High"));
	if (nIndex != CB_ERR) {
		m_cbTempMode.SetItemData(nIndex, TempModeHigh);
	}

	nIndex = m_cbNRF.InsertString(m_cbNRF.GetCount(), _T("Off"));
	if (nIndex != CB_ERR) {
		m_cbNRF.SetItemData(nIndex, OffSensitivity);
	}
	nIndex = m_cbNRF.InsertString(m_cbNRF.GetCount(), _T("Low"));
	if (nIndex != CB_ERR) {
		m_cbNRF.SetItemData(nIndex, LowSensitivity);
	}
	nIndex = m_cbNRF.InsertString(m_cbNRF.GetCount(), _T("Middle"));
	if (nIndex != CB_ERR) {
		m_cbNRF.SetItemData(nIndex, MiddleSensitivity);
	}
	nIndex = m_cbNRF.InsertString(m_cbNRF.GetCount(), _T("High"));
	if (nIndex != CB_ERR) {
		m_cbNRF.SetItemData(nIndex, HighSensitivity);
	}

	nIndex = m_cbEdgeEnhance.InsertString(m_cbEdgeEnhance.GetCount(), _T("Off"));
	if (nIndex != CB_ERR) {
		m_cbEdgeEnhance.SetItemData(nIndex, OffSensitivity);
	}
	nIndex = m_cbEdgeEnhance.InsertString(m_cbEdgeEnhance.GetCount(), _T("Low"));
	if (nIndex != CB_ERR) {
		m_cbEdgeEnhance.SetItemData(nIndex, LowSensitivity);
	}
	nIndex = m_cbEdgeEnhance.InsertString(m_cbEdgeEnhance.GetCount(), _T("Middle"));
	if (nIndex != CB_ERR) {
		m_cbEdgeEnhance.SetItemData(nIndex, MiddleSensitivity);
	}
	nIndex = m_cbEdgeEnhance.InsertString(m_cbEdgeEnhance.GetCount(), _T("High"));
	if (nIndex != CB_ERR) {
		m_cbEdgeEnhance.SetItemData(nIndex, HighSensitivity);
	}

	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("Off"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCOff);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("1 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin1);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("2 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin2);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("3 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin3);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("4 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin4);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("5 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin5);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("10 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin10);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("20 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin20);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("30 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin30);
	}
	nIndex = m_cbNUCTime.InsertString(m_cbNUCTime.GetCount(), _T("60 min"));
	if (nIndex != CB_ERR) {
		m_cbNUCTime.SetItemData(nIndex, NUCMin60);
	}

	nIndex = m_cbNUCAuto.InsertString(m_cbNUCAuto.GetCount(), _T("Off"));
	if (nIndex != CB_ERR) {
		m_cbNUCAuto.SetItemData(nIndex, OffSensitivity);
	}
	nIndex = m_cbNUCAuto.InsertString(m_cbNUCAuto.GetCount(), _T("Low"));
	if (nIndex != CB_ERR) {
		m_cbNUCAuto.SetItemData(nIndex, LowSensitivity);
	}
	nIndex = m_cbNUCAuto.InsertString(m_cbNUCAuto.GetCount(), _T("Middle"));
	if (nIndex != CB_ERR) {
		m_cbNUCAuto.SetItemData(nIndex, MiddleSensitivity);
	}
	nIndex = m_cbNUCAuto.InsertString(m_cbNUCAuto.GetCount(), _T("High"));
	if (nIndex != CB_ERR) {
		m_cbNUCAuto.SetItemData(nIndex, HighSensitivity);
	}
}

void CThermalCtrlInfoDlg::Initialize()
{
	ZeroMemory(&m_thermalComponents, sizeof(m_thermalComponents));
	m_thermalComponents.ulStructSize = sizeof(m_thermalComponents);

	long ret = SPIDER_GetThermalCtrlInfo(theApp.m_hSelectCamera, &m_thermalComponents);
	if (ret == E_CTRL_OK) {
		m_edtThermalVer.SetWindowText(m_thermalComponents.szThermalAPIVer);
		m_btnThermalCorrection.EnableWindow(m_thermalComponents.bEnableCOR ? TRUE:FALSE);
		
		ZeroMemory(&m_thermalCtrlValue, sizeof(m_thermalCtrlValue));
		ret = SPIDER_GetThermalCtrlValue(theApp.m_hSelectCamera, &m_thermalCtrlValue);
		if (ret == E_CTRL_OK) {
			m_edtThermalVer.SetWindowText(m_thermalComponents.szThermalAPIVer);
			SetCtrlValue();
		} else {
			MessageBox(_T("Could not get thermal ctrl value"));
		}
	} else {
		MessageBox(_T("Could not get thermal ctrl info"));
	}
}

void CThermalCtrlInfoDlg::SetCtrlValue()
{
	for (int i=0; i<m_cbPalette.GetCount(); i++) {
		if (m_cbPalette.GetItemData(i) == m_thermalCtrlValue.emPaletteClr) {
			m_cbPalette.SetCurSel(i);
			break;
		}
	}
	m_btnShowTemp.EnableWindow(m_thermalComponents.bEnableCOL ? TRUE:FALSE);
	
	m_bClrInvert = (m_thermalCtrlValue.emVidInvert == ThermalOn) ? TRUE:FALSE;
	m_btnClrInvert.EnableWindow((!m_thermalComponents.bEnableCIT || m_thermalCtrlValue.emVidInvert == NotSupportOnOff) ? FALSE:TRUE);

	m_bGainAuto = (m_thermalCtrlValue.emVidAgc == AgcAuto) ? TRUE:FALSE;
	if (m_thermalComponents.bEnableAGC && m_thermalCtrlValue.emVidAgc != NotSupportAgc) {
		m_btnGainManual.EnableWindow(TRUE);
		m_btnGainAuto.EnableWindow(TRUE);
	} else {
		m_btnGainManual.SetCheck(BST_CHECKED);
		m_btnGainAuto.SetCheck(BST_UNCHECKED);

		m_btnGainManual.EnableWindow(FALSE);
		m_btnGainAuto.EnableWindow(FALSE);
	}

	m_edtGainMin.EnableWindow(m_bGainAuto ? FALSE:TRUE);
	m_edtGainMax.EnableWindow(m_bGainAuto ? FALSE:TRUE);
	
	m_nlGainMin		= m_thermalCtrlValue.nlManualGainMin;
	m_nlGainMax		= m_thermalCtrlValue.nlManualGainMax;
	m_nlBrightness	= m_thermalCtrlValue.nlBrightness;
	m_nlContrast	= m_thermalCtrlValue.nlContrast;

	for (int i=0; i<m_cbTempMode.GetCount(); i++) {
		if (m_cbTempMode.GetItemData(i) == m_thermalCtrlValue.emTempMode) {
			m_cbTempMode.SetCurSel(i);
			break;
		}
	}
	m_cbTempMode.EnableWindow((!m_thermalComponents.bEnableTRM || m_thermalCtrlValue.emTempMode == NotSupportTempMode) ? FALSE:TRUE);

	for (int i=0; i<m_cbNRF.GetCount(); i++) {
		if (m_cbNRF.GetItemData(i) == m_thermalCtrlValue.emNRF) {
			m_cbNRF.SetCurSel(i);
			break;
		}
	}
	m_cbNRF.EnableWindow((!m_thermalComponents.bEnableNRF || m_thermalCtrlValue.emNRF == NotSupportSensitivity) ? FALSE:TRUE);

	for (int i=0; i<m_cbEdgeEnhance.GetCount(); i++) {
		if (m_cbEdgeEnhance.GetItemData(i) == m_thermalCtrlValue.emEdgeEnhance) {
			m_cbEdgeEnhance.SetCurSel(i);
			break;
		}
	}
	m_cbNRF.EnableWindow((!m_thermalComponents.bEnableEEH || m_thermalCtrlValue.emEdgeEnhance == NotSupportSensitivity) ? FALSE:TRUE);

	for (int i=0; i<m_cbNUCTime.GetCount(); i++) {
		if (m_cbNUCTime.GetItemData(i) == m_thermalCtrlValue.emVidSysNuc) {
			m_cbNUCTime.SetCurSel(i);
			break;
		}
	}
	m_cbNRF.EnableWindow((!m_thermalComponents.bEnableNTE || m_thermalCtrlValue.emVidSysNuc == NotSupportSysNUC) ? FALSE:TRUE);

	for (int i=0; i<m_cbNUCAuto.GetCount(); i++) {
		if (m_cbNUCAuto.GetItemData(i) == m_thermalCtrlValue.emNUCAutoMode) {
			m_cbNUCAuto.SetCurSel(i);
			break;
		}
	}
	m_cbNRF.EnableWindow((!m_thermalComponents.bEnableNAT || m_thermalCtrlValue.emNUCAutoMode == NotSupportSensitivity) ? FALSE:TRUE);

	m_bShowCenter		= (m_thermalCtrlValue.emShowCenter == ThermalOn) ? TRUE:FALSE;
	m_btnShowCenter.EnableWindow((!m_thermalComponents.bEnableSCR || m_thermalCtrlValue.emShowCenter == NotSupportOnOff) ? FALSE:TRUE);

	m_bShowIndicator	= (m_thermalCtrlValue.emShowIndi == ThermalOn) ? TRUE:FALSE;
	m_btnShowIndicator.EnableWindow((!m_thermalComponents.bEnableSID || m_thermalCtrlValue.emShowIndi == NotSupportOnOff) ? FALSE:TRUE);

	m_bShowTemperature	= (m_thermalCtrlValue.emShowTemp == ThermalOn) ? TRUE:FALSE;
	m_btnShowTemp.EnableWindow((!m_thermalComponents.bEnableSTP || m_thermalCtrlValue.emShowTemp == NotSupportOnOff) ? FALSE:TRUE);

	m_bShowClrBar		= (m_thermalCtrlValue.emShowPalette == ThermalOn) ? TRUE:FALSE;
	m_btnShowClrBar.EnableWindow((!m_thermalComponents.bEnableSCB || m_thermalCtrlValue.emShowPalette == NotSupportOnOff) ? FALSE:TRUE);

	UpdateData(FALSE);
}

void CThermalCtrlInfoDlg::OnBnClickedRadioGain()
{
	UpdateData();

	m_edtGainMin.EnableWindow(m_bGainAuto ? FALSE:TRUE);
	m_edtGainMax.EnableWindow(m_bGainAuto ? FALSE:TRUE);
}

void CThermalCtrlInfoDlg::OnBnClickedButtonThermalModify()
{
	if (!UpdateData()) {
		return;
	}

	ST_SPIDER_THERMAL_CTRL_ADV prevThermalCtrlValue;
	memcpy(&prevThermalCtrlValue, &m_thermalCtrlValue, sizeof(ST_SPIDER_THERMAL_CTRL_ADV));

	if (m_cbPalette.IsWindowEnabled()) {
		m_thermalCtrlValue.emPaletteClr = (EM_THERMAL_PALETTE)m_cbPalette.GetItemData(m_cbPalette.GetCurSel());
	}
	if (m_btnClrInvert.IsWindowEnabled()) {
		m_thermalCtrlValue.emVidInvert = m_bClrInvert ? ThermalOn : ThermalOff;
	}

	if (m_btnGainAuto.IsWindowEnabled()) {
		m_thermalCtrlValue.emVidAgc = m_bGainAuto ? AgcAuto : AgcManual;
	}

	m_thermalCtrlValue.nlManualGainMin = m_nlGainMin;
	m_thermalCtrlValue.nlManualGainMax = m_nlGainMax;

	if (m_edtBrightness.IsWindowEnabled()) {
		m_thermalCtrlValue.nlBrightness = m_nlBrightness;
	}
	if (m_edtContrast.IsWindowEnabled()) {
		m_thermalCtrlValue.nlContrast = m_nlContrast;
	}

	if (m_cbTempMode.IsWindowEnabled()) {
		m_thermalCtrlValue.emTempMode = (EM_THERMAL_TEMP_MODE)m_cbTempMode.GetItemData(m_cbTempMode.GetCurSel());
	}
	if (m_cbNRF.IsWindowEnabled()) {
		m_thermalCtrlValue.emNRF = (EM_THERMAL_SENSITIVITY)m_cbNRF.GetItemData(m_cbNRF.GetCurSel());
	}
	if (m_cbEdgeEnhance.IsWindowEnabled()) {
		m_thermalCtrlValue.emEdgeEnhance = (EM_THERMAL_SENSITIVITY)m_cbEdgeEnhance.GetItemData(m_cbEdgeEnhance.GetCurSel());
	}
	if (m_cbNUCTime.IsWindowEnabled()) {
		m_thermalCtrlValue.emVidSysNuc = (EM_THERMAL_SYSNUC)m_cbNUCTime.GetItemData(m_cbNUCTime.GetCurSel());
	}
	if (m_cbNUCAuto.IsWindowEnabled()) {
		m_thermalCtrlValue.emNUCAutoMode = (EM_THERMAL_SENSITIVITY)m_cbNUCAuto.GetItemData(m_cbNUCAuto.GetCurSel());
	}
	
	if (m_btnShowCenter.IsWindowEnabled()) {
		m_thermalCtrlValue.emShowCenter = m_bShowCenter ? ThermalOn : ThermalOff;
	}
	if (m_btnShowIndicator.IsWindowEnabled()) {
		m_thermalCtrlValue.emShowIndi = m_bShowIndicator ? ThermalOn : ThermalOff;
	}
	if (m_btnShowTemp.IsWindowEnabled()) {
		m_thermalCtrlValue.emShowTemp = m_bShowTemperature ? ThermalOn : ThermalOff;
	}
	if (m_btnShowClrBar.IsWindowEnabled()) {
		m_thermalCtrlValue.emShowPalette = m_bShowClrBar ? ThermalOn : ThermalOff;
	}

	long nlResult = SPIDER_SetThermalCtrlValue(theApp.m_hSelectCamera, m_thermalCtrlValue);
	if (nlResult == E_CTRL_OK) {
		MessageBox(_T("Success."));
	} else {
		MessageBox(GetErrorString(nlResult), ("Fail"));
		memcpy(&m_thermalCtrlValue, &prevThermalCtrlValue, sizeof(ST_SPIDER_THERMAL_CTRL_ADV));
		SetCtrlValue();
	}
}




void CThermalCtrlInfoDlg::OnBnClickedButtonSetRegionAlarm()
{
	CThermalRegionInfoDlg dlg(&m_thermalComponents);
	dlg.DoModal();
}


void CThermalCtrlInfoDlg::OnBnClickedButtonThermalCorrection()
{
	CThermalCorrectionInfoDlg dlg(&m_thermalComponents);
	dlg.DoModal();
}


void CThermalCtrlInfoDlg::OnBnClickedButtonGetRegionAlarm()
{
	CThermalTempInfoDlg dlg;
	dlg.DoModal();
}


void CThermalCtrlInfoDlg::OnBnClickedButtonSetNuc()
{
	long nlResult = SPIDER_ExeThermalNUC(theApp.m_hSelectCamera);
	if (nlResult == E_CTRL_OK) {
		MessageBox(_T("Success."));
	} else {
		MessageBox(GetErrorString(nlResult), ("Fail"));
	}
}
