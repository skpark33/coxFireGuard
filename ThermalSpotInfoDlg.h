#pragma once
#include "afxwin.h"


// CThermalSpotInfoDlg 대화 상자입니다.

class CThermalSpotInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CThermalSpotInfoDlg)

public:
	CThermalSpotInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThermalSpotInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THERMAL_SPOT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	ST_SPIDER_THERMAL_SPOT_INFO m_stThermalSpotInfo;

	CString m_strMinCoordinate;
	CString m_strMaxCoordinate;

	CComboBox m_cbEnable[10];
	CButton m_btnModify[10];

protected:
	void CreateEnableComboBox();
	void ModifyThermalSpot(ST_SPIDER_THERMAL_SPOT* pSpot);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonGet2();
	afx_msg void OnBnClickedButtonModify1();
	afx_msg void OnBnClickedButtonModify2();
	afx_msg void OnBnClickedButtonModify3();
	afx_msg void OnBnClickedButtonModify4();
	afx_msg void OnBnClickedButtonModify5();
	afx_msg void OnBnClickedButtonModify6();
	afx_msg void OnBnClickedButtonModify7();
	afx_msg void OnBnClickedButtonModify8();
	afx_msg void OnBnClickedButtonModify9();
	afx_msg void OnBnClickedButtonModify10();
};
