#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CTimeInfoDlg dialog

class CTimeInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CTimeInfoDlg)

public:
	CTimeInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTimeInfoDlg();


// Dialog Data
	enum { IDD = IDD_TIME_INFO, IDH = IDR_HTML_TIMEINFODLG };


	ST_SPIDER_TIME_INFO		m_stInfo;
	vector<ST_SPIDER_TIME_NTPSERVER_INFO>		m_vInfo;

	void InitInfo();
	void DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_TimeMode;
	CListCtrl m_List_NTPServer;
	CComboBox m_Combo_NTPServerFormatType;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickListNtpServer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListNtpServer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonTimeModify();
	afx_msg void OnBnClickedButtonNtpModify();
	afx_msg void OnBnClickedButtonNtpAdd();
	afx_msg void OnBnClickedButtonNtpDelete();
};
