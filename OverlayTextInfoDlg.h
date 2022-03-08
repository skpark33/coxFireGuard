#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// COverlayTextInfoDlg dialog

class COverlayTextInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(COverlayTextInfoDlg)

public:
	COverlayTextInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COverlayTextInfoDlg();


// Dialog Data
	enum { IDD = IDD_OVERLAY_TEXT_INFO, IDH = IDR_HTML_OVERLAYTEXTINFODLG };


	vector<ST_SPIDER_TEXT_INFO>		m_vInfo;


	void InitInfo();
	void DisplayInfo();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CListCtrl m_List_Overlay;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedListOverlay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListOverlay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonModifyOverlay();
	afx_msg void OnBnClickedButtonAddOverlay();
	afx_msg void OnBnClickedButtonDeleteOverlay();
};
