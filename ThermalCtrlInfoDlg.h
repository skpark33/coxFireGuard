#pragma once
#include "afxwin.h"


// CThermalCtrlInfoDlg 대화 상자입니다.

class CThermalCtrlInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CThermalCtrlInfoDlg)

public:
	CThermalCtrlInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThermalCtrlInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THERMAL_CTRL_INFO };

protected:
	ST_SPIDER_THERMAL_COMPONENTS m_thermalComponents;
	ST_SPIDER_THERMAL_CTRL_ADV m_thermalCtrlValue;

	CEdit m_edtThermalVer;
	CComboBox m_cbPalette;
	CButton m_btnClrInvert;
	CButton m_btnGainManual;
	CButton m_btnGainAuto;
	CEdit m_edtGainMin;
	CEdit m_edtGainMax;
	CEdit m_edtBrightness;
	CEdit m_edtContrast;
	CComboBox m_cbTempMode;
	CComboBox m_cbNRF;
	CComboBox m_cbEdgeEnhance;
	CComboBox m_cbNUCTime;
	CComboBox m_cbNUCAuto;
	CButton m_btnShowCenter;
	CButton m_btnShowIndicator;
	CButton m_btnShowTemp;
	CButton m_btnShowClrBar;

	long m_nlGainMin;
	long m_nlGainMax;
	long m_nlBrightness;
	long m_nlContrast;

	BOOL m_bClrInvert;
	BOOL m_bGainAuto;
	BOOL m_bShowCenter;
	BOOL m_bShowIndicator;
	BOOL m_bShowTemperature;
	BOOL m_bShowClrBar;

protected:
	void CreateCtrl();

	void Initialize();
	void SetCtrlValue();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioGain();
	afx_msg void OnBnClickedButtonThermalModify();
	CButton m_btnSetRegionAlarm;
	CButton m_btnThermalCorrection;
	afx_msg void OnBnClickedButtonSetRegionAlarm();
	afx_msg void OnBnClickedButtonThermalCorrection();
	afx_msg void OnBnClickedButtonGetRegionAlarm();
	afx_msg void OnBnClickedButtonSetNuc();
};
