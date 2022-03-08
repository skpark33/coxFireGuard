#pragma once
#include "afxwin.h"


// CThermalTempInfoDlg 대화 상자입니다.

class CThermalTempInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CThermalTempInfoDlg)

public:
	CThermalTempInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CThermalTempInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THERMAL_TEMPERATURE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CStatic m_wndTempValidEntire;
	CStatic m_wndTempAlarmEntire;
	CEdit m_edtTempCenterEntire;
	CEdit m_edtTempMinEntire;
	CEdit m_edtTempMaxEntire;
	CEdit m_edtTempAvgEntire;
	LONG m_nlMinXEntire;
	LONG m_nlMinYEntire;
	LONG m_nlMaxXEntire;
	LONG m_nlMaxYEntire;
	
	CStatic m_wndTempValid[10];
	CStatic m_wndTempAlarm[10];
	CEdit m_edtTempCenter[10];
	CEdit m_edtTempMin[10];
	CEdit m_edtTempMax[10];
	CEdit m_edtTempAvg[10];
	LONG m_nlMinX[10];
	LONG m_nlMinY[10];
	LONG m_nlMaxX[10];
	LONG m_nlMaxY[10];

	afx_msg void OnBnClickedButton1();
public:
	virtual BOOL OnInitDialog();
};
