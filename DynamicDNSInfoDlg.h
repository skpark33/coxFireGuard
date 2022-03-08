#pragma once
#include "afxwin.h"


// CDynamicDNSInfoDlg 대화 상자입니다.

class CDynamicDNSInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDynamicDNSInfoDlg)

public:
	CDynamicDNSInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDynamicDNSInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DYNAMIC_DNS_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CComboBox m_cbEnable;
	CComboBox m_cbDNSSvcName;
	CEdit m_edtHostName;
	CEdit m_edtUserName;
	CEdit m_edtPwd;
	CEdit m_edtHashCode;
	CEdit m_edtPeriod;
	CButton m_edtModify;
	CString m_strHostName;
	CString m_strUserName;
	CString m_strPwd;
	CString m_strHashCode;
	long m_nlPeriod;

protected:
	void InitDDNS();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInputModify();
	afx_msg void OnCbnSelchangeComboEnable();
};
