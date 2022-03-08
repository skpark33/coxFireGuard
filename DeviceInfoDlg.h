#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CDeviceInfoDlg dialog

class CDeviceInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CDeviceInfoDlg)

public:
	CDeviceInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeviceInfoDlg();


// Dialog Data
	enum { IDD = IDD_DEVICE_INFO, IDH = IDR_HTML_DEVICEINFODLG };





	ST_SPIDER_DEVICE_INFO m_stInfo;









protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonModify();
};
