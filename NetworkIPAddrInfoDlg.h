#pragma once

#ifdef _WIN32_WCE
#error "CDialog is not supported for Windows CE."
#endif 

// CNetworkIPAddrInfoDlg dialog

class CNetworkIPAddrInfoDlg : public CDialog
{
	DECLARE_DYNCREATE(CNetworkIPAddrInfoDlg)

public:
	CNetworkIPAddrInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNetworkIPAddrInfoDlg();


// Dialog Data
	enum { IDD = IDD_NETWORK_IPADDR_INFO, IDH = IDR_HTML_NETWORKIPADDRINFODLG };


	vector<ST_SPIDER_NETWORK_INFO>		m_vNetwork;
	ST_SPIDER_NETWORK_IPADDR_INFO		m_stIPAddr;
	ST_SPIDER_NETWORK_DISCOVERY_INFO	m_stDiscovery;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_NetworkID;
	CComboBox m_Combo_IPVersion;
	CComboBox m_Combo_IPAddressType;
	CButton m_Check_Upnp;
	CButton m_Check_ZeroConf;
	CButton m_Check_MultiCast;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonApplyIpaddress();
	afx_msg void OnCbnSelchangeComboNetworkId();
	afx_msg void OnBnClickedButtonApplyDiscovery();
};
