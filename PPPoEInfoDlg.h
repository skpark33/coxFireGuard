#pragma once
#include "afxwin.h"


// CPPPoEInfoDlg 대화 상자입니다.

class CPPPoEInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPPPoEInfoDlg)

public:
	CPPPoEInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPPPoEInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PPPOE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_edtID;
	CEdit m_edtPwd;
	CString m_strID;
	CString m_strPwd;
	CButton m_btnModify;

protected:
	void InitPPPoE();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonModify();
};
