#pragma once
#include "afxwin.h"


// CThermalCorrectionInfoDlg 대화 상자입니다.

class CThermalCorrectionInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CThermalCorrectionInfoDlg)

public:
	CThermalCorrectionInfoDlg(ST_SPIDER_THERMAL_COMPONENTS* pThermalComponents, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThermalCorrectionInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THERMAL_CORRECTION_INFO };

protected:
	ST_SPIDER_THERMAL_COMPONENTS* m_pThermalComponents;
	ST_SPIDER_THERMAL_CORRECT_INFO m_thermalCorrectInfo;

	CButton m_btnEnable;
	CEdit m_edtEmissivity;
	CEdit m_edtTransmission;
	CEdit m_edtAtmosphere;
	CEdit m_edtZeroOffset;
	CEdit m_edtDistCorr;

	float m_fEmissivity;
	float m_fTransmission;
	float m_fAtmosphere;
	float m_fZeroOffset;
	long m_nlDistCorr;

protected:
	void Initialize();
	void SetCtrlValue();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckEnable();
	BOOL m_bEnable;
	afx_msg void OnBnClickedButtonThermalModify();
};
