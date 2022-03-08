#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CCustomTriggerInfoDlg dialog

class CCustomTriggerInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CCustomTriggerInfoDlg)

public:
	CCustomTriggerInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomTriggerInfoDlg();


// Dialog Data
	enum { IDD = IDD_CUSTOM_TRIGGER_INFO, IDH = IDR_HTML_CUSTOMTRIGGERINFODLG };


	ST_SPIDER_CUSTOM_TRIGGER_INFO		m_stInfo;
	vector<ST_SPIDER_CUSTOM_TRIGGER_PARAM_INFO>		m_vInfo;


	void InitInfo();
	void DisplayInfoParam();
	void DisplayInfoTrigger();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModifyTrigger();
	afx_msg void OnNMClickListParam(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_List_Param;
	afx_msg void OnBnClickedButtonModifyParam();
	CComboBox m_Combo_Source;
	CComboBox m_Combo_Polarity;
	CComboBox m_Combo_TriggerServerOnOff;
	afx_msg void OnBnClickedButtonSetTrigger();
	afx_msg void OnBnClickedButtonAdd();
	CComboBox m_Combo_CaptureFileSaving;
	afx_msg void OnCbnSelchangeComboPolarity();
	afx_msg void OnCbnSelchangeComboSource();
	CComboBox m_Combo_TriggerImage;
	afx_msg void OnCbnSelchangeComboCaptureFormat();
	afx_msg void OnCbnSelchangeComboCaptureFileSaving();
	CComboBox m_Combo_TableOnOff;
	afx_msg void OnCbnSelchangeComboTableOnoff();
};
