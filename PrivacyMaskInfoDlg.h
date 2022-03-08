#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CPrivacyMaskInfoDlg dialog

class CPrivacyMaskInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CPrivacyMaskInfoDlg)

public:
	CPrivacyMaskInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrivacyMaskInfoDlg();


// Dialog Data
	enum { IDD = IDD_PRIVACY_MASK_INFO, IDH = IDR_HTML_PRIVACYMASKINFODLG };


	ST_SPIDER_PRIVACYMASK		m_stInfo;
	vector<ST_SPIDER_PRIVACYMASK_REGION>		m_vInfo;

	void InitInfo();
	void DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_RegionID;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnCbnSelchangeComboPrivacyId();
	afx_msg void OnBnClickedButtonAddRegion();
	afx_msg void OnBnClickedButtonDeleteRegion();
};
