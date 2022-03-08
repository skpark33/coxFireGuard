#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CMotionInfoDlg dialog

class CMotionInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CMotionInfoDlg)

public:
	CMotionInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMotionInfoDlg();


// Dialog Data
	enum { IDD = IDD_MOTION_INFO, IDH = IDR_HTML_MOTIONINFODLG };


	ST_SPIDER_MOTION		m_stInfo;
	vector<ST_SPIDER_MOTION_REGION>		m_vInfo;


	void InitInfo();
	void DisplayInfo();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_DirectionSensitivity;
	CComboBox m_Combo_RegionID;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboMotionId();
	afx_msg void OnBnClickedButtonModifyMotion();
	afx_msg void OnBnClickedButtonModifyRegion();
	afx_msg void OnBnClickedButtonAddRegion();
	afx_msg void OnBnClickedButtonDeleteRegion();
};
