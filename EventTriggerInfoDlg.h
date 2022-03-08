#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CEventTriggerInfoDlg dialog

class CEventTriggerInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CEventTriggerInfoDlg)

public:
	CEventTriggerInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEventTriggerInfoDlg();


// Dialog Data
	enum { IDD = IDD_EVENT_TRIGGER_INFO, IDH = IDR_HTML_EVENTTRIGGERINFODLG };


	vector<ST_SPIDER_EVENT_TRIGGER_INFO>		m_vInfo;


	void InitInfo();
	void DisplayInfo();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_EventType;
	CComboBox m_Combo_NotifyMethod;
	CTreeCtrl m_TreeTrigger;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModifyNotify();
	afx_msg void OnTvnSelchangedTreeTrigger(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonModifyTrigger();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonAddNotify();
	afx_msg void OnBnClickedButtonDeleteNotify();
	afx_msg void OnNMDblclkTreeTrigger(NMHDR *pNMHDR, LRESULT *pResult);
};
