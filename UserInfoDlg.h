#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CUserInfoDlg dialog

class CUserInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUserInfoDlg();


// Dialog Data
	enum { IDD = IDD_USER_INFO, IDH = IDR_HTML_USERINFODLG };


	vector<ST_SPIDER_USER_ACCOUNT_INFO>		m_vInfo;


	void InitInfo();
	void DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CListCtrl m_List_User;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
};
