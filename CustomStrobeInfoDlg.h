#pragma once
#include "afxwin.h"

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CCustomStrobeInfoDlg dialog

class CCustomStrobeInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CCustomStrobeInfoDlg)

public:
	CCustomStrobeInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomStrobeInfoDlg();


// Dialog Data
	enum { IDD = IDD_CUSTOM_STROBE_INFO, IDH = IDR_HTML_CUSTOMSTROBEINFODLG };


	vector<ST_SPIDER_CUSTOM_STROBE_INFO>		m_vInfo;

	void DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	CListCtrl m_List_Strobe;
	afx_msg void OnNMClickListStrobe(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_Combo_Strobe;
	CComboBox m_Combo_Polarity;
public:
	afx_msg void OnBnClickedButtonApply();
	CComboBox m_Combo_StrobeMode;
	afx_msg void OnCbnSelchangeComboStrobeMode();
};
