#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CNotifyMailingInfoDlg dialog

class CNotifyMailingInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CNotifyMailingInfoDlg)

public:
	CNotifyMailingInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNotifyMailingInfoDlg();


// Dialog Data
	enum { IDD = IDD_NOTIFY_MAILING_INFO, IDH = IDR_HTML_NOTIFYMAILINGINFODLG };


	ST_SPIDER_EVENT_NOTIFICATION						m_stInfo;
	vector<ST_SPIDER_EVENT_NOTIFICATION_MAILING>		m_vInfo;

	void InitInfo();
	void DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CListCtrl m_List_Mail;
	CComboBox m_Combo_AuthMode;
	CComboBox m_Combo_AddressFormat;
	CComboBox m_Combo_POPAddressFormat;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickListMail(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonModifyNotification();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
};
