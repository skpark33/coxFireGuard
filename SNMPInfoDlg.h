#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSNMPInfoDlg 대화 상자입니다.

class CSNMPInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CSNMPInfoDlg)

public:
	CSNMPInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSNMPInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SNMP_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

protected:
	CComboBox m_cbSNMPEnable;
	CComboBox m_cbCstEnable;
	CIPAddressCtrl m_ipctrlCst;
	CButton m_btnModify;

protected:
	void InitSNMP();

public:
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnCbnSelchangeComboSnmpEnable();
	afx_msg void OnCbnSelchangeComboCstEnable();
};
