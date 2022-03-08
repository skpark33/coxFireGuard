#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CNetworkIPFilterInfoDlg dialog

class CNetworkIPFilterInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CNetworkIPFilterInfoDlg)

public:
	CNetworkIPFilterInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNetworkIPFilterInfoDlg();


// Dialog Data
	enum { IDD = IDD_NETWORK_IPFILTER_INFO, IDH = IDR_HTML_NETWORKIPFILTERINFODLG };


	CString _GetAddressText(ST_SPIDER_NETWORK_IPFILTER_ADDRESS stAddress);

	vector<ST_SPIDER_NETWORK_INFO>		m_vNetwork;
	ST_SPIDER_NETWORK_IPFILTER		m_stInfo;
	vector<ST_SPIDER_NETWORK_IPFILTER_ADDRESS>	m_vInfo;

	void DisplayInfo();
	void DisplayInfo_Address();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_NetworkID;
	CComboBox m_Combo_Permission;
	CListCtrl m_List_Address;
	CComboBox m_Combo_AddressPermission;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboNetworkId();
	afx_msg void OnNMClickListIpfilter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonModifyIpfilter();
	afx_msg void OnBnClickedButtonModifyAddress();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
};
